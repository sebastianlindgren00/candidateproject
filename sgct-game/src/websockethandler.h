/*****************************************************************************************
 *                                                                                       *
 * WebSocket Handler                                                                     *
 *                                                                                       *
 * Copyright (c) Alexander Bock, 2020                                                    *
 *                                                                                       *
 * All rights reserved.                                                                  *
 *                                                                                       *
 * Redistribution and use in source and binary forms, with or without modification, are  *
 * permitted provided that the following conditions are met:                             *
 *                                                                                       *
 * 1. Redistributions of source code must retain the above copyright notice, this list   *
 *    of conditions and the following disclaimer.                                        *
 *                                                                                       *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this     *
 *    list of conditions and the following disclaimer in the documentation and/or other  *
 *    materials provided with the distribution.                                          *
 *                                                                                       *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY   *
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES  *
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT   *
 * SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,        *
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED  *
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR    *
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN      *
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN    *
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH   *
 * DAMAGE.                                                                               *
 ****************************************************************************************/

#ifndef __WEBSOCKETHANDLER_H__
#define __WEBSOCKETHANDLER_H__

#include <functional>
#include <memory>
#include <string>

struct WebSocketHandlerImpl;

/**
 * This class handles a websocket connection using the libwebsocket library.  To establish
 * a connection, first create an instance of this class using the address of the remote
 * address you want to connect to, the port at which to connect to the remote, and
 * callbacks for when messages are received through this socket connection (see below).
 * Then call the #connect method with a specific protocolName (which has to match the
 * clients parameter in the <code>new WebSocket(url, 'protocol')</code> call) and a buffer
 * size in which a received message has to fit.
 * 
 * After that, the #tick method has to be called regularly (preferrably every frame) by
 * your application to be able to receive messages.
 *
 * If you want send a message to the client, you can queue a message to be sent using the
 * #queueMessage method, which will add the message to the queue handled internally.  At
 * any point you can query the size of the queue through the #queueSize method.
 *
 * You can prematurely close the connection through the #disconnect message.
 *
 * Callbacks:
 *  - <code>connectionEstablished</code> This callback is called when the inital
 *    handshaking has been performed and the connection is ready to be used
 *  - <code>connectionClosed</code> This callback is called when the connection is closed
 *    by the remote host.  The same WebSocketHandler instance can then be reused in a
 *    subsequent #connect call to initialize a new connection
 *  - <code>messageReceived</code> This callback is called when a new message is received
 *    from the remote host.  The parameters to the callback are a pointer to the message
 *    and the length of the message in bytes.
 */
class WebSocketHandler {
public:
    WebSocketHandler(std::string address, int port,
        std::function<void()> connectionEstablished,
        std::function<void()> connectionClosed,
        std::function<void(const void*, size_t)> messageReceived);

    ~WebSocketHandler();

    bool connect(std::string protocolName, int bufferSize);
    void disconnect();
    bool isConnected() const;
    void tick();

    void queueMessage(std::string message);
    void queueMessage(std::vector<std::byte> message);
    int queueSize() const;

private:
    std::unique_ptr<WebSocketHandlerImpl> _pImpl;
};

#endif // __WEBSOCKETHANDLER_H__
