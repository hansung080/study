var http = require('http');

function parseCookie(cookie) {
	return cookie.split(';').map(function (element) {
		var element = element.split('=');
		return {
			name: element[0],
			value: element[1]
		};
	});
}

http.createServer(function (request, response) {
	var date = new Date();
	date.setDate(date.getDate() + 7)

	var cookie = request.headers.cookie;
	cookie = parseCookie(cookie);

	response.writeHead(200, {
		'Content-Type': 'text/html',
		'Set-Cookie': [
			'breakfast=toast; Expires='+date.toUTCString(),
			'dinner=chicken'
		]
	});

	response.end('<h1>'+JSON.stringify(cookie)+'</h1>')

}).listen(52273, function () {
	console.log('server is running at 52273');
});