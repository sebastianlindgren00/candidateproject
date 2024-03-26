const serverAddress = 'wss://omni.itn.liu.se/ws/';
var socket;

function log(msg) {
    document.getElementById('debug-output').innerHTML = msg;
    console.log(msg);
}

function initialize() {
  socket = new WebSocket(serverAddress);
  socket.onopen = function(event) {
    log('Connection is opened');
  };

  socket.onerror = function (err) {
    log(`Error: ${err}`);
  }

  socket.onclose = function() {
    log('Connection is closed');
  }

  socket.onmessage = function() {
    log(event.data);
  }
}
