var http = require('http');
var express = require('express');

var app = express();

app.use(express.cookieParser());
app.use(express.session({
	secret: 'secret key',
	key: 'kwon',
	cookie: {
		maxAge: 10 * 1000
	}
}));
app.use(express.bodyParser());
app.use(function (request, response) {
	var output = {};
	output.cookies = request.cookies;
	output.session = request.session;

	request.session.now = new Date().toUTCString();

	response.send(output);
});

http.createServer(app).listen(52273, function (err) {
	console.log('server is running at 52273');
});