var timer = require('./timer');

timer.ticker.on('tick', function () {
	console.log('tick event occurs');
});