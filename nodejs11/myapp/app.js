var express = require('express');
var app = express();
var fs = require('fs');

const bodyParser = require('body-parser'); 
app.use(bodyParser.urlencoded({extended:false})); 
app.use(bodyParser.json());

app.get('*', function(request, response, next){
    fs.readdir('./data', function(error, filelist){
      request.list = filelist;
      next();
    });
  });

app.use('/default', require('./html/option'));

// app.use(function(req, res, next) {
//   res.status(404).send('Sorry cant find that!');
// });

app.use('/', express.static('./temp'));
// app.get('/', (req, res) => {
//   res.sendFile(path.join(__dirname, + '/html/control_send_page.html'));
// })



var server = app.listen(3000, () => {
    console.log('app listening on port : 8000');
});
