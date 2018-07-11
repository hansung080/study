var http = require('http');
var fs = require('fs');
var express = require('express'); // npm install express@3.4.7
var socketio = require('socket.io'); // npm install socket.io@0.9.19

/**
	seats description
	0: no seats
	1: available: enable
	2: reserved: disable
*/
var seats = [
	[1, 1, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 1, 1],
	[1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1],
	[1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1],
	[1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1],
	[1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1],
	[1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1],
	[1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1],
	[1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1],
	[1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1],
	[1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1],
	[1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1],
	[1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1]
];

var app = express();

app.use(app.router);

app.get('/', function (request, response, next) {
	fs.readFile('movie_reservation.html', function (error, data) {
		response.send(data.toString());
	});
});

app.get('/seats', function (request, response, next) {
	response.send(seats);
});

var server = http.createServer(app).listen(52273, function () {
	console.log('http server is running at 52273');
});

var io = socketio.listen(server);

io.sockets.on('connection', function (socket) {
	socket.on('reserve', function (pos) {
		seats[pos.y][pos.x] = 2;
		io.sockets.emit('reserve', pos);
	});
});
