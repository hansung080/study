var net = require('net');
var util = require('./util');

var socket = net.connect(52273, '127.0.0.1', function () {
	console.log('echo client is connected to 127.0.0.1:52273');
});

socket.on('data', function (data) {
	util.println('echo:', data.toString('utf8'));
});

process.stdin.resume();
process.stdin.on('data', function (chunk) {
	if (chunk.toString('utf8') == 'quit\n') {
		process.exit(0);
	} else {
		socket.write(chunk);	
	}
});
