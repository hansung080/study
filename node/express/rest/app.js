var http = require('http');
var express = require('express');
var db = require('./db').db;

var app = express();

app.use(express.bodyParser());
app.use(app.router);

app.get('/user', function (request, response) {
	response.send(db.select());
});

app.get('/user/:id', function (request, response) {
	response.send(db.select(request.param('id')));
});

app.post('/user', function (request, response) {
	var name = request.param('name');
	var age = request.param('age');

	response.send(db.insert({
		name: name,
		age: age
	}));
});

app.put('/user/:id', function (request, response) {});
app.delete('/user/:id', function (request, response) {});

http.createServer(app).listen(52273, function () {
	console.log('server is running at 52273');
});