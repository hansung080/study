var http = require('http');
var fs = require('fs');

http.createServer(function (request, response) {
	fs.readFile('hello.html', function (err, data) {
		response.writeHead(200, {'Content-Type': 'text/html'});
		response.end(data);
	});

}).listen(52273, function () {
	console.log('server is running at 52273');
});
