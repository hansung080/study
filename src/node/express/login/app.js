http = require('http');
express = require('express');
fs = require('fs');

var app = express();

//app.use(express.logger('default'));
app.use(express.cookieParser());
app.use(express.bodyParser());
app.use(app.router);

app.get('/', function (request, response) {
	if (request.cookies.auth) {
		response.send('<h1>Login Success</h1>');
	} else {
		response.redirect('/login');
	}
});

app.get('/login', function (request, response) {
	fs.readFile('login.html', function (err, data) {
		response.send(data.toString());
	});
});

app.post('/login', function (request, response) {
	var id = request.param('id');
	var password = request.param('password');

	if (id == 'kwon' && password == '1234') {
		response.cookie('auth', true);
		response.redirect('/');
	} else {
		response.redirect('/login');
	}
});

http.createServer(app).listen(52273, function () {
	console.log('server is running at 52273');
});
