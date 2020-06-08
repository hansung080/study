var net = require('net');
var util = require('./util');

net.createServer(function (socket) {
	socket.on('data', function (data) {
		util.println('received:', data.toString('utf8'))
		socket.write(data);
	});

}).listen(52273, function () {
	console.log('echo server is running at 52273');
});