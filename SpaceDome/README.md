# SGCT-Networked-Application
A basic template to create an SGCT application that opens a WebSocket to listen to input coming through a single connection.

To clone this repository, don't forget to recurse submodules: `git clone --recurse-submodules https://github.com/alexanderbock/SGCT-Networked-Application.git` or the dependent libraries will not work correctly.

# Getting started
1. Execute `npm install` in the `webserver` folder
2. Compile the application
3. Start the web server with `node server.js` in the `webserver` folder
4. Start the application
5. Connect from a second device

In the current version, it is necessary to start the server *before* starting the application, as the application will only try to connect once at startup.

# Configurations
Currently, the server and application addresses are encoded in several places that all have to be changed:
1. `webserver/server.js` has a `port` and `gameAddress` that have to point at the machine that is running the application.
2. The application's `src/main.cpp` creates a `WebSocketHandler`, whose constructor requires the IP address and port of the webserver.
3. The `webserver/public/script.js` sets a `serverAddress` variable that has to point to the game server location.
