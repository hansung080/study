var EventEmitter;
if (process.EventEmitter) {
	EventEmitter = process.EventEmitter;
} else {
	EventEmitter = require('events');
}

exports.ticker = new EventEmitter();

setInterval(function () {
	exports.ticker.emit('tick');
}, 1000);