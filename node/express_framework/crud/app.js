
/**
 * Module dependencies.
 */

var express = require('express');
var routes = require('./routes');
var product = require('./routes/product');
var http = require('http');
var path = require('path');

var app = express();

// all environments
app.set('port', process.env.PORT || 3000);
app.set('views', path.join(__dirname, 'views'));
app.set('view engine', 'ejs');
app.use(express.favicon());
app.use(express.logger('dev'));
app.use(express.json());
app.use(express.urlencoded());
app.use(express.methodOverride());
app.use(app.router);
app.use(express.static(path.join(__dirname, 'public')));

// development only
if ('development' == app.get('env')) {
  app.use(express.errorHandler());
}

app.get('/', routes.index);
app.get('/product/list', product.getListPage);
app.get('/product/insert', product.getInsertPage);
app.post('/product/insert', product.insertProduct);
app.get('/product/edit/:id', product.getEditPage);
app.post('/product/edit/:id', product.editProduct);
app.get('/product/delete/:id', product.deleteProduct);

http.createServer(app).listen(app.get('port'), function(){
  console.log('Express server listening on port ' + app.get('port'));
});
