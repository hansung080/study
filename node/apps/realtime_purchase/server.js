var http = require('http');
var fs = require('fs');
var express = require('express'); // npm install express@3.4.7
var ejs = require('ejs'); // npm install ejs
var socketio = require('socket.io'); // npm install socket.io@0.9.19

var counter = 0;
function Product(name, image, price, count) {
	this.index = counter++;
	this.name = name;
	this.image = image;
	this.price = price;
	this.count = count;
}

var products = [
	new Product('Android Phone', 'android_phone.jpg', 150000, 100),
	new Product('iPhone', 'iphone.jpg', 230000, 100),
	new Product('Laptop', 'laptop.jpg', 370000, 100),
	new Product('Desktop', 'desktop.jpg', 410000, 100),
	new Product('Television', 'television.jpg', 550000, 100),
	new Product('Speaker', 'speaker.jpg', 680000, 100),
	new Product('Vacuum Cleaner', 'vacuum_cleaner.jpg', 740000, 100)
];

var app = express();
var server = http.createServer(app);

app.use(app.router);
app.use(express.static(__dirname + '/public'));

app.get('/', function (request, response) {
	var html = fs.readFileSync('store.html', 'utf8');
	response.send(ejs.render(html, {
		products: products
	}));
});

server.listen(52273, function () {
	console.log('server is running at 52273');
});

var io = socketio.listen(server);
io.sockets.on('connection', function (socket) {
	function onReturn(index) {
		console.log('return event:', index);

		products[index].count++;

		clearTimeout(cart[index].timerId);
		delete cart[index];

		io.sockets.emit('count', {
			index: index,
			count: products[index].count
		});		
	}

	var cart = {};

	socket.on('cart', function (index) {
		console.log('cart event:', index);

		products[index].count--;

		cart[index] = {};
		cart[index].index = index;
		cart[index].timerId = setTimeout(function () {
			onReturn(index);
			socket.emit('return', index);

		}, 1000 * 30); // 30 seconds

		io.sockets.emit('count', {
			index: index,
			count: products[index].count
		});
	});

	socket.on('buy', function (index) {
		console.log('buy event:', index);

		clearTimeout(cart[index].timerId);
		delete cart[index];

		io.sockets.emit('count', {
			index: index,
			count: products[index].count
		});
	});

	socket.on('return', function (index) {
		onReturn(index);
	});
});
