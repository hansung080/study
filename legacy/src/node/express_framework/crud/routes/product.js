var mysql = require('mysql');

var client = mysql.createConnection({
	user: 'root',
	password: 'kwon1226',
	database: 'nodejs'
});

exports.getListPage = function (req, res) {
	client.query('SELECT * FROM products;', function (error, results) {
		res.render('product/list', {
			data: results
		});
	});
}

exports.getInsertPage = function (req, res) {
	res.render('product/insert');
}

exports.insertProduct = function (req, res) {
	var body = req.body;
	client.query('INSERT INTO products (name, modelnumber, series) VALUES (?, ?, ?);', [body.name, body.modelnumber, body.series], function () {
		res.redirect('/product/list');
	});
}

exports.getEditPage = function (req, res) {
	client.query('SELECT * FROM products WHERE id=?;', [req.param('id')], function (error, results) {
		res.render('product/edit', {
			data: results[0]
		});
	});
}

exports.editProduct = function (req, res) {
	var body = req.body;
	client.query('UPDATE products SET name=?, modelnumber=?, series=? WHERE id=?;', [body.name, body.modelnumber, body.series, req.param('id')], function () {
		res.redirect('/product/list');
	});
}

exports.deleteProduct = function (req, res) {
	client.query('DELETE FROM products WHERE id=?;', [req.param('id')], function () {
		res.redirect('/product/list');
	});
}
