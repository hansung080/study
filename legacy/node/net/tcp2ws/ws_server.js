/**
	@ websocket
	https://tools.ietf.org/html/rfc6455
*/

var net = require('net');
var crypto = require('crypto');

var guid = '258EAFA5-E914-47DA-95CA-C5AB0DC85B11';

net.createServer(function (socket) {
	socket.on('data', function (data) {
		// websocket upgrade request
		if (/websocket/.test(data.toString())) {
			console.log('========== websocket upgrade request ==========');
			var headers = data.toString().split('\n');
			var requestKey = '';
			headers.forEach(function (header) {
				var dict = header.split(':');
				if (dict.length == 2 && dict[0].toLowerCase().trim() == 'sec-websocket-key') {
					requestKey = dict[1].trim();
				}
			});

			var longKey = requestKey + guid;
			var shasum = crypto.createHash('sha1').update(longKey);
			var responseKey = shasum.digest('base64');

			socket.write('HTTP/1.1 101 Switching Protocols\r\n');
			socket.write('Upgrade: WebSocket\r\n');
			socket.write('Connection: Upgrade\r\n');
			socket.write('Sec-WebSocket-Accpet: '+responseKey+'\r\n');
			socket.write('\r\n');

			setInterval(function () {
				var message = 'message from server';
				var buffer = new Buffer(message.length + 2);
				buffer[0] = 0x81 // 1000 0001
				buffer[1] = message.length; // mask:0, payload len: message.len
				for (var i = 0; i < message.length; i++) {
					buffer[i + 2] = message.charCodeAt(i); // payload: message
				}
				socket.write(buffer);

			}, 1000);

		// http request
		} else if (/HTTP/.test(data.toString())) {
			console.log('========== http request ==========');
			var body = [];
			body.push('<script>');
			body.push('	var socket = new WebSocket("ws://127.0.0.1:52273/");');
			body.push('	socket.onopen = function (event) {');
			body.push('		alert("websocket open");');
			body.push('		setInterval(function () {');
			body.push('			socket.send("message from client");');
			body.push('		}, 1000);');
			body.push('	};');
			body.push('	socket.onerror = function (event) {');
			body.push('		alert("websocket error: "+event);');
			body.push('	};');
			body.push('	socket.onmessage = function (event) {');
			body.push('		alert("websocket message: "+event.data);');
			body.push('	};');
			body.push('	socket.onclose = function (event) {');
			body.push('		alert("websocket close");');
			body.push('	};');
			body.push('</script>');

			body = body.join('\n');

			socket.write('HTTP/1.1 200 OK\r\n');
			socket.write('Server: Hans Server\r\n');
			socket.write('Content-Type: text/html\r\n');
			socket.write('Content-Length: '+body.length+'\r\n');
			socket.write('\r\n');
			socket.write(body);
			socket.end();
		
		// websocket request	
		} else {
			console.log('========== websocket request ==========');
			var opcode = data[0] & 0x0F;
			var payloadLen = data[1];
			var mask = [data[2], data[3], data[4], data[5]];
			var buffer = new Buffer(payloadLen);
			for (var i = 6; i < payloadLen + 6; i++) {
				buffer += String.fromCharCode(data[i] ^ mask[(i - 5) % 4]);
			}

			console.log('websocket request message:', buffer);
		}
	});

}).listen(52273, function () {
	console.log('web socket server is running at 52273');
});
