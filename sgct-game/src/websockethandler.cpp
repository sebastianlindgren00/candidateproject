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

#include "websockethandler.h"

#include <sgct/profiling.h>
#include "libwebsockets.h"
#include <algorithm>
#include <assert.h>
#include <exception>
#include <mutex>
#include <string_view>
#include <vector>

/// Private implementation (=pimpl) of the WebSocketHandler to hide all details in here
struct WebSocketHandlerImpl {
    /// Address that we want to connect to
    std::string address;
    /// Port at which to connect
    int port = 0;

    /// Mutex that protects simulteanoues access to the messageQueue
    std::mutex messageMutex;
    /// The queued list of messages that will be sent one-by-one, whenever the sockets
    /// reports that it is ready to be written to
    std::vector<std::vector<std::byte>> messageQueue;

    /// The user's function pointer that is called when a connection is established
    std::function<void()> connectionEstablished;
    /// The user's function pointer that is called when the connection is terminated
    std::function<void()> connectionClosed;
    /// The user's function pointer that is called when a message was received, which
    /// includes the data of the message
    std::function<void(const void*, size_t)> messageReceived;

    bool isConnected = false;

    /// The disconnect method sets this to \c true.  We can't disconnect the socket
    /// directly, but have to wait for a round-trip through the callback method, which
    /// needs to return -1 in order to signal to libwebsocket that it should close it.
    /// ¯\_(ツ)_/¯
    bool wantsToDisconnect = false;

    /// A pointer to the context that contains our protocol and connection
    lws_context* context = nullptr;

    /// The currently active connection
    lws* connection = nullptr;
};

int callback(lws* wsi, lws_callback_reasons reason, void* u, void* in, size_t len) {
    ZoneScoped

    // We need this extra check as in some of the early callbacks the protocol doesn't
    // seem to be fully initialized and will return a nullptr.  But we don't handle any of
    // these early callbacks in our switch, so the pImpl being nullptr won't be a problem.
    //
    // If you find this message because your program crashed:  I'm sorry and please open
    // an issue on https://github.com/alexanderbock/SGCT-Networked-Application so that I
    // can fix this
    void* usr = lws_get_protocol(wsi) ? lws_get_protocol(wsi)->user : nullptr;
    WebSocketHandlerImpl* pImpl = reinterpret_cast<WebSocketHandlerImpl*>(usr);

    if (pImpl && pImpl->wantsToDisconnect) {
        pImpl->wantsToDisconnect = false;
        return -1;
    }

    switch (reason) {
        case LWS_CALLBACK_CLIENT_ESTABLISHED:
            assert(pImpl);
            pImpl->isConnected = true;
            pImpl->connectionEstablished();
            lws_callback_on_writable(wsi);
            break;
        case LWS_CALLBACK_CLIENT_RECEIVE:
            assert(pImpl);
            pImpl->messageReceived(in, len);
            break;
        case LWS_CALLBACK_CLIENT_WRITEABLE:
        {
            ZoneScopedN("Write to WebSocket")

            assert(pImpl);
            std::lock_guard lock(pImpl->messageMutex);
            if (pImpl->messageQueue.empty()) {
                break;
            }

            // Get a copy of first message from the queue.  Don't change this into a
            // reference or we will have a dangling reference after the following erase
            std::vector<std::byte> msg = pImpl->messageQueue.front();
            pImpl->messageQueue.erase(pImpl->messageQueue.begin());

            // Libwebsocket requires a padding in the beginning to include
            // websocket-related information.  This is seems quite a dirty way of handling
            // this, but what do I know ¯\_(ツ)_/¯
            std::vector<std::byte> buffer(LWS_PRE + msg.size());
            // Null out the entire block, just to be sure we don't send any garbage
            std::fill(buffer.begin(), buffer.end(), std::byte(0));
            // Insert the message in the middle block
            std::copy(msg.begin(), msg.end(), buffer.begin() + LWS_PRE);

            // Send the message.
            // Yes, we have to pass the pointer past the padding and send the size of the
            // message, not the buffer...  that is not an error -.-
            unsigned char* p = reinterpret_cast<unsigned char*>(buffer.data() + LWS_PRE);
            lws_write(wsi, p, msg.size(), LWS_WRITE_TEXT);
            break;
        }
        case LWS_CALLBACK_CLIENT_CLOSED:
        case LWS_CALLBACK_CLOSED:
        case LWS_CALLBACK_CLIENT_CONNECTION_ERROR:
            assert(pImpl);
            pImpl->connectionClosed();
            pImpl->isConnected = false;
            pImpl->connection = nullptr;
            pImpl->context = nullptr;
            return -1; // close the connection
        case LWS_CALLBACK_CLOSED_CLIENT_HTTP:
        case LWS_CALLBACK_WSI_DESTROY:
            // For some reason or another, our connection is dead, so if we don't want to
            // make any more tick() calls (and cause a crash), we gotta get rid of our
            // own pointers.  The actual memory underneath has already been taken care of
            // by the libwebsockets library
            assert(pImpl);
            pImpl->connection = nullptr;
            pImpl->context = nullptr;
            return -1;
        default:
            break;
    }

    return 0;
}

WebSocketHandler::WebSocketHandler(std::string address, int port,
                                   std::function<void()> connectionEstablished,
                                   std::function<void()> connectionClosed,
                                   std::function<void(const void*, size_t)> msgReceived)
{
    // Check whether there is a valid address
    assert(!address.empty());

    // Check whether the port is a valid (>0) number
    assert(port > 0);

    // Check whether the callbacks provided are non-empty
    assert(connectionEstablished);
    assert(msgReceived);

    // Create our private implementation
    _pImpl = std::make_unique<WebSocketHandlerImpl>();
    _pImpl->address = std::move(address);
    _pImpl->port = port;
    _pImpl->connectionEstablished = std::move(connectionEstablished);
    _pImpl->connectionClosed = std::move(connectionClosed);
    _pImpl->messageReceived = std::move(msgReceived);
}

WebSocketHandler::~WebSocketHandler() {
    disconnect();
    tick();

    lws_context_destroy(_pImpl->context);
    _pImpl = nullptr;
}

bool WebSocketHandler::connect(std::string protocolName, int bufferSize) {
    ZoneScoped

    assert(bufferSize >= 0);

    lws_context_creation_info info;
    std::memset(&info, 0, sizeof(info));

    info.port = CONTEXT_PORT_NO_LISTEN;

    // This is a bit ugly;  we pass in the address to the callbacks structure so that we
    // can access it as the user pointer of the protocol inside the callback function
    // whenever something interesting happens in the websocket connection
    const size_t bufSize = static_cast<size_t>(bufferSize);
    const lws_protocols protocols[] = {
        { protocolName.c_str(), callback, 0, bufSize, 0, _pImpl.get() },
        { nullptr, nullptr, 0, 0, 0, nullptr } // terminal value
    };

    info.protocols = protocols;
    info.gid = -1;
    info.uid = -1;

    _pImpl->context = lws_create_context(&info);
    lws_client_connect_info ccinfo;
    std::memset(&ccinfo, 0, sizeof(ccinfo));
    ccinfo.context = _pImpl->context;
    ccinfo.address = _pImpl->address.c_str();
    ccinfo.port = _pImpl->port;
    ccinfo.path = "/";
    ccinfo.host = lws_canonical_hostname(_pImpl->context);
    ccinfo.origin = "origin";
    ccinfo.protocol = protocols[0].name;

    _pImpl->connection = lws_client_connect_via_info(&ccinfo);
    return _pImpl->connection != nullptr;
}

void WebSocketHandler::disconnect() {
    if (_pImpl->context && _pImpl->connection) {
        _pImpl->wantsToDisconnect = true;
        lws_callback_on_writable(_pImpl->connection);
    }
}

bool WebSocketHandler::isConnected() const {
    return _pImpl->isConnected;
}

void WebSocketHandler::tick() {
    ZoneScoped

    if (_pImpl->context && _pImpl->connection) {
        lws_callback_on_writable(_pImpl->connection);
        lws_service(_pImpl->context, 0);
    }
}

void WebSocketHandler::queueMessage(std::string message) {
    std::vector<std::byte> msg(message.size());
    std::transform(
        message.begin(), message.end(),
        msg.begin(),
        [](char c) { return static_cast<std::byte>(c); }
    );
    queueMessage(std::move(msg));
}

void WebSocketHandler::queueMessage(std::vector<std::byte> message) {
    std::lock_guard lock(_pImpl->messageMutex);
    _pImpl->messageQueue.push_back(std::move(message));
}

int WebSocketHandler::queueSize() const {
    std::lock_guard lock(_pImpl->messageMutex);
    return static_cast<int>(_pImpl->messageQueue.size());
}
