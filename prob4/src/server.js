'use strict';

const PORT = 8080;
const HOST = '0.0.0.0';

var express = require('express');
var app = express();

var bodyParser = require('body-parser');
//require('body-parser-xml')(bodyParser);
//app.use(bodyParser.xml());
app.use(bodyParser.text({ type: 'text/plain'}));

var router = require('./router/main')(app);

app.set('views', __dirname + '/views');
app.set('view engine', 'ejs');
app.use(express.static('public'));
app.engine('html', require('ejs').renderFile);

var server = app.listen(PORT, HOST, function() {
	console.log(`Running on http://${HOST}:${PORT}`);
});



