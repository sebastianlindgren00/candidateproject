from websockets.sync.client import connect, ClientConnection
from websockets.exceptions import ConnectionClosed
import socket
import threading
import queue
import json

PORT = 4685
SERVER = "localhost"
DISCONNECT_MESSAGE = "!DISCONNECT"

omniConnected = False
osConnected = False

tokenMessage = ''

threads = []

OmniQueue = queue.Queue()
OpenSpaceQueue = queue.Queue()

osOutgoingCondition = threading.Condition()
omniOutgoingCondition = threading.Condition()

# CHANGE HERE: Client outgoing messages
def osOutgoingMessages(client : socket.socket):
    """Send messages to OpenSpace from Omni input queue"""
    # On connection with server we always send token message, this allows OS to reconnect
    # without having to restart the proxy server
    if osConnected and omniConnected:
        print("msg to OS:", tokenMessage)
        client.send((tokenMessage + "\n").encode())

    while osConnected and omniConnected:
        with osOutgoingCondition:
            if OpenSpaceQueue.empty():
                osOutgoingCondition.wait()

            if not osConnected or not omniConnected:
                client.close()
                break

            # Retrieve messages that came from omni
            message = OpenSpaceQueue.get()
            message += "\n"
            # jmessage = json.dumps(message)
            # Send message to os
            print("msg to OS:", message)
            message = message.encode()
            client.send(message)

# CHANGE HERE: Client incoming messages
def osIncomingmessages(client : socket.socket):
    """Recieve messages from OpenSpace which are put in the output Omni queue"""

    global osConnected
    while osConnected and omniConnected:
        try:
            message = client.recv(1024).decode()
            if message:
                with omniOutgoingCondition:
                    # Put them in omni queue for passthrough
                    print("msg from OS:", message)
                    OmniQueue.put(message)
                    omniOutgoingCondition.notify()
            else:
                print("Error receiving data from OpenSpace. Connection closed.")
                osConnected = False
                with osOutgoingCondition:
                    osOutgoingCondition.notify_all()
        except OSError as e:
            osConnected = False
            print(f"Connection closed: {e}")

def omniOutgoingMessages(client : ClientConnection):
    """Send messages to Omni from OpenSpace input queue"""

    while omniConnected:
        with omniOutgoingCondition:
            if OmniQueue.empty():
                omniOutgoingCondition.wait()

            # We might have been notified by a disconnect so we check
            # if we are still connected
            if not omniConnected:
                break

            # Retrieve messages that came from OpenSpace
            message = OmniQueue.get()
            # Send them to omni
            client.send(message)

def omniIncommingMessages(client : ClientConnection):
    """Recieve messages from Omni which are put in the output OpenSpace queue"""

    while omniConnected:
        try:
            # Retrieve messsages from omni
            message = client.recv()
            with osOutgoingCondition:
                # Put them in OpenSpace queue for passthrough
                OpenSpaceQueue.put(message)
                print("omni inc:", message)
                osOutgoingCondition.notify()
        except ConnectionClosed:
            # We notify the outgoing omni thread that we have disconnected
            with omniOutgoingCondition:
                omniOutgoingCondition.notify_all()

            with osOutgoingCondition:
                osOutgoingCondition.notify_all()


def connectOmniWebsocket() -> ClientConnection:
    websocketClient = connect('wss://omni.itn.liu.se/ws/')
    # Recieve welcome message
    message = websocketClient.recv()
    print(f'Recieved: {message}')
    # Send token to authenticate
    websocketClient.send(json.dumps({"token": 'eebbeb2c-7bca-44ad-b7f2-25515e053ce9'}))
    # Recieve authentication message
    message = websocketClient.recv()
    message = json.loads(message)
    print(f'Recieved: {message}')

    if not message['type'] == 'server_authorized':
        print(f'Failed to authenticate: {message["message"]}')
        return None

    # Recieve token message, which we store if OS needs to reconnect
    message = websocketClient.recv()
    # message = json.loads(message)

    global tokenMessage
    tokenMessage = message

    global omniConnected
    omniConnected = True

    threadInc = threading.Thread(
        target=omniIncommingMessages,
        args=(websocketClient,),
        name="Omni incomming messages"
    )
    threadOut = threading.Thread(
        target=omniOutgoingMessages,
        args=(websocketClient,),
        name="Omni outgoing messages"
    )
    threads.append(threadInc)
    threads.append(threadOut)

    return websocketClient


def serverLoop(server : socket.socket):
    """Setup server loop listening for connections comming from the client"""
    while omniConnected:
        try:
            client, addr = server.accept()

            if not omniConnected:
                return

            print(f"[NEW CONNECTION] {addr} connected.")
            global osConnected
            osConnected = True
            threadInc = threading.Thread(
                target=osIncomingmessages,
                args=(client,),
                name="OpenSpace incomming messages"
            )
            threadOut = threading.Thread(
                target=osOutgoingMessages,
                args=(client,),
                name="OpenSpace outgoing messages"
            )
            threads.append(threadInc)
            threads.append(threadOut)
            threadInc.start()
            threadOut.start()
        except OSError as e:
            print(f"Local server shutdown: {e}")

def createLocalhostServer() -> socket.socket:
    # Create localhost server
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind((SERVER, PORT))
    print("[STARTING] server is starting...")
    server.listen()
    print(f"[LISTENING] Server is listening on {SERVER}:{PORT}")

    serverT = threading.Thread(target=serverLoop, args=(server,), name="Server loop")
    threads.append(serverT)
    return server


client = connectOmniWebsocket()
if client is None:
    print("Failed to connect to Omni")
    exit()

server = createLocalhostServer()

# Start all incoming and outgoing threads to handle communication.
for thread in threads:
    thread.start()

# Easy way to disconnect the server and client
input("Press Enter to disconnect\n")
omniConnected = False
osConnected = False

client.close()
# Not the best solution, but in order to get out of the server 'while loop'
# we make a new local connection to the server since its waiting at the .accept() call
socket.socket(socket.AF_INET, socket.SOCK_STREAM).connect((SERVER, PORT))
server.close()

print("Joining threads...")
for thread in threads:
    print(f"Joining thread: {thread.name}")

    thread.join()

print("All threads joined. Exiting...")