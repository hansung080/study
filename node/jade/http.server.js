var http = require('http');
var fs = require('fs');
var jade = require('jade');

http.createServer(function (request, response) {
	fs.readFile('profile.jade', 'utf8', function (err, data) {
		response.writeHead(200, {'Content-Type': 'text/html'});
		response.end(jade.compile(data)({
			name: 'kwon',
			desc: 'I love playing soccer.'
		}));
	});

}).listen(52273, function () {
	console.log('server is runnig at 52273');
});
