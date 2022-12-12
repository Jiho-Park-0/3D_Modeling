var express = require('express') //express 모듈
var app = express() //함수
var fs = require('fs');
var path = require('path');
var qs = require('querystring');
var bodyParser = require('body-parser');
var compression = require('compression');
var template = require('./lib/template.js');
var topicRouter = require('./routes/topic');
var indexRouter = require('./routes/index');

var helmet = require('helmet') //보호
app.use(helmet());
 
app.use(express.static('public'));
app.use(bodyParser.urlencoded({ extended: false }));
app.use(compression());

app.get('*', function(request, response, next){
  fs.readdir('./data', function(error, filelist){
    request.list = filelist;
    next();
  });
});
 
app.use('/topic', topicRouter);
app.use('/', indexRouter);
 
app.use(function(req, res, next) {
  res.status(404).send('Sorry cant find that!');
});
 
app.use(function (err, req, res, next) {
  console.error(err.stack)
  res.status(500).send('Something broke!')
});
 
app.listen(3000, function() {
  console.log('Example app listening on port 3000!')
});