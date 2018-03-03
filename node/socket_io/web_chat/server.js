var http = require('http');
var fs = require('fs');
var socketio = require('socket.io'); // npm install socket.io@0.9.19

var server = http.createServer().listen(52273, function () {
	console.log('http server is running at 52273');
});

server.on('request', function (request, response) {
	var htmlPage = '';
	if (request.headers['user-agent'].match(/Android|iPhone|iPad|iPod/)) {
		htmlPage = 'mobile_chat.html';
	} else {
		htmlPage = 'web_chat.html';
	}

	fs.readFile(htmlPage, function (error, data) {
		response.writeHead(200, {
			'Content-Type': 'text/html'
		});

		response.end(data);
	});
});

var io = socketio.listen(server);

io.sockets.on('connection', function (socket) {
	socket.on('message', function (message) {
		io.sockets.emit('message', message);
	});
});
