'use strict'

//
// This template for this file is heavily inspired by the 2019 TNM094 group;
// @gunnarsdotter @Anondod @ylvaselling @SimonKallberg
// When you see them, buy them a beer; they saved you about 2 weeks of work
//

const express = require('express');
const app = express();
const server = require('http').Server(app);
const WebSocketServer = require('websocket').server;

//
// 
const port = 80;
const gameAddress = 'wss://omni.itn.liu.se/ws/';

app.use(express.static(__dirname + '/public'));

app.get('/', function (req, res) {
  res.sendFile(__dirname + '/public/index.html');
});

server.listen(port, function () {
  console.log(`Server is listening on: ${server.address().address}:${port}`);
})

var gameSocket = null;
var connectionArray = [];

var wsServer = new WebSocketServer({ httpServer: server });
wsServer.on('request', function (req) {
  if (req.remoteAddress === gameAddress) {
    console.log('Game connection');

    gameSocket = req.accept("example-protocol", req.origin);

    gameSocket.on('message', function(msg) {
      if (msg.type === 'utf8') {
        if (msg.utf8Data === 'ping') {
          gameSocket.send('pong');
        }
      }
    });

    gameSocket.on('close', function(reason, desc) {
      console.log(`Game connection lost. Reason: ${reason}.  Description: ${desc}`);
      gameSocket = null;
    });
  }
  else {
    console.log(`Other connection from ${req.remoteAddress}`);

    const addresses = connectionArray.map(c => c.socket.remoteAddress);
    if (addresses.indexOf(req.remoteAddress) === -1 || connectionArray.length === 0) {
      // Save the connection for later use
      var connection = req.accept(null, req.origin);
      connectionArray.push(connection);

      connection.send('Connected');

      // Do something with the connection
      connection.on('message', function(msg) {
        if (msg.type === 'utf8') {

        }
      });

      // When the connection closes
      connection.on('close', function(reason, desc) {
        const addresses = connectionArray.map(c => c.socket.remoteAddress);
        connectionArray.splice(addresses.indexOf(connection.socket.remoteAddress), 1);
      });
    }
    else {
      console.log('Same IP address connected twice');
    }

    if (gameSocket) {
      gameSocket.send(req.remoteAddress);
    }
  }
});
