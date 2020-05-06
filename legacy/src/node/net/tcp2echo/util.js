exports.println = function (msg, data) {
	if (data.charAt(data.length - 1) == '\n') {
		console.log(msg, data.substring(0, data.length - 1));
	} else {
		console.log(msg, data);
	}
}