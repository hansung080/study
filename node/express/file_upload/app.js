var http = require('http');
var express = require('express');
var fs = require('fs');

var app = express();

app.use(express.cookieParser());
app.use(express.limit('10mb'));
app.use(express.bodyParser({uploadDir: __dirname + '/upload'}));
app.use(app.router);

app.get('/', function (request, response) {
	fs.readFile('file_upload.html', function (err, data) {
		response.send(data.toString());
	});
});

app.post('/', function (request, response) {
	var comment = request.param('comment');
	var file = request.files.file;
	
	if (file) {
		var name = file.name;
		var path = file.path;
		var type = file.type;

		console.log('comment: %s, name: %s, path: %s, type: %s', comment, name, path, type);

		if (type.indexOf('image') != -1) {
			var repath = __dirname + '/upload/' + Date.now() + '_' + name;
			fs.rename(path, repath, function (err) {
				response.redirect('/');
			});

		} else {
			fs.unlink(path, function (err) {
				response.send(404);
			});
		}

	} else {
		response.send(404);
	}
});

http.createServer(app).listen(52273, function () {
	console.log('server is runnig at 52273');
});
