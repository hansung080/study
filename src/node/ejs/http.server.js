var http = require('http');
var fs = require('fs');
var ejs = require('ejs');

http.createServer(function (request, response) {
	fs.readFile('profile.ejs', 'utf8', function (err, data) {
		response.writeHead(200, {'Content-Type': 'text/html'});
		response.end(ejs.render(data, {
			name: 'kwon',
			age: 35
		}));
	});

}).listen(52273, function () {
	console.log('server is running at 52273');
});
