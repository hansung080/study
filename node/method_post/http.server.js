var http = require('http');
var fs = require('fs');

http.createServer(function (request, response) {
	if (request.method == 'GET') {
		fs.readFile('profile.html', function (err, data) {
			response.writeHead(200, {'Content-Type': 'text/html'});
			response.end(data);
		});

	} else if (request.method == 'POST') {
		request.on('data', function (data) {
			response.writeHead(200, {'Content-Type': 'text/html'});
			response.end('<h1>'+data+'</h1>');
		});
	}

}).listen(52273, function () {
	console.log('server is running at 52273');
});

