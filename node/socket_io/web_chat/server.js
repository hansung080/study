var http = require('http');
var fs = require('fs');
var socketio = require('socket.io');

var server = http.createServer().listen(52273, function () {
	console.log('server is running at 52273');
});

server.on('request', function (request, response) {
	fs.readFile('client.html', function (error, data) {
		response.writeHead(200, {
			'Content-Type': 'text/html'
		});

		response.end(data);
	});
});

var io = socketio.listen(server);

io.sockets.on('connection', function (socket) {
	socket.on('message', function (message) {
		socket.emit('message', message);
	});
});
