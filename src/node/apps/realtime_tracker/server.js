var fs = require('fs');
var http = require('http');
var express = require('express'); // npm install express@3.4.7
var socketio = require('socket.io'); // npm install socket.io@0.9.19
var mysql = require('mysql'); // npm install mysql

var db = mysql.createConnection({
	user: 'root',
	password: 'kwon1226',
	database: 'nodejs'
});

var app = express();
var server = http.createServer(app);

app.get('/tracker', function (request, response) {
	fs.readFile('tracker.html', function (error, data) {
		response.send(data.toString());
	});
});

app.get('/observer', function (request, response) {
	fs.readFile('observer.html', function (error, data) {
		response.send(data.toString());
	});
});

app.get('/showdata', function (request, response) {
	db.query('SELECT * FROM locations WHERE name=?'
		    ,[request.param('name')]
		    ,function (error, data) {
		response.send(data.toString());
	});
});

server.listen(52273, function () {
	console.log('server is running at 52273');
});

var io = socketio.listen(server);
io.sockets.on('connection', function (socket) {
	socket.on('join', function (name) {
		socket.join(name);
	});

	socket.on('location', function (loc) {
		db.query('INSERT INTO locations(name, latitude, longitude, date) VALUES (?, ?, ?, NOW())'
				,[loc.name, loc.latitude, loc.longitude]);

		io.sockets.in(loc.name).emit('receive', {
			latitude: loc.latitude,
			longitude: loc.longitude,
			date: new Date()
		});
	});
});
