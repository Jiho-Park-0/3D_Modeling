var express = require('express');
var app = express();

app.use('/', require('./html/option'));

var server = app.listen(8000, () => {
    console.log('app listening on port : 8000');
});