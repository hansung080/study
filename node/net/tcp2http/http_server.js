var net = require('net');

net.createServer(function (socket) {
	var body = '<h1>Hello World!</h1>';
	socket.write('HTTP/1.1 200 OK\n');
	socket.write('Server: Hans Server\n');
	socket.write('Content-Type: text/html\n');
	socket.write('Content-Length: '+body.length+'\n');
	socket.write('\n');
	socket.write(body);

}).listen(52273, function () {
	console.log('http server is running at 52273');
});
