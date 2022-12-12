const { json } = require('express');
var express = require('express');
var fs = require('fs');
var router = express.Router();
var path = require('path');
var request = require('request');
var template = require('../template/template.js');
var control_tempalte = require('../template/control.js');
var qs = require('querystring');
var fsExtra = require('fs-extra');


router.get('/', (req, res, next) => res.sendFile(__dirname + '/main.html'));
router.post('/', (req, res, next) => {
  var post = req.body;
  var title = post.title;
  fsExtra.emptyDirSync('html/index');
  // var jsonDataObj = { name : `${title}`};
  // request.post({
  //   url: 'http://13.125.205.44:3000/index',
  //   body: jsonDataObj,
  //   json: true
  // }, function(error, response, body){
  //   res.json(body);
  //   console.log("success to send!");
  // })

  const options = {
    url: 'http://13.125.205.44:3000/index',
    qs:{
      name:title
    }
  };
  request(options,function(err,response,body){
    console.log("success to send!");
  })

  if(!fs.existsSync(`./data/${title}`)) fs.mkdirSync(`./data/${title}`);

  var description = `
  var express = require('express');
  const { fstat } = require('fs');
  var router = express.Router();
  var path = require('path');

  var way = path.join(__dirname, 'temp');
  console.log(way);
  router.use(express.static(way));

  module.exports = router;
  `;
  fs.writeFile(`./data/${title}/${title}.js`, description, 'utf8', function(err){});
  res.write("<script>alert('Success to send to Arduino')</script>");
  res.write("<script>window.location=\"../default\"</script>");
  //res.redirect('/default');
  
  next();
});

router.get('/send', function (req, res) {

  res.sendFile(__dirname + '/send.html')

});
router.post('/send', (req, res, next) => { 


    //마지막 json { final : '1' }
    var start = JSON.stringify(req.body.start);
    var finish = JSON.stringify(req.body.finish);
    
    var description = JSON.stringify(req.body);
    console.log(description);
    fs.writeFile(`html/index/${start}.json`, description, 'utf8', function(err){
        if(err) throw err;
        res.send('성공!');
        //res.send("<script>alert('your alert message'); window.location.href = \"/\"; </script>");
    })
    if(finish == 1){
      console.log("Finish!");
    }
  //next();
});


router.get('/modeling', function(req, res) { 
    var title = 'Modeling List';

    var list = template.list(req.list);
    var html = template.HTML(title, list); 
    res.send(html);
    
  });
router.post('/modeling', (req, res, next) => {
    
});

router.get('/index', (req, res, next) => {
  res.redirect('/');
});

router.use('/control', require('./control'));
router.get('/control', (req, res, next) => {
  
  var data = fs.readFileSync('html/coordinate', 'utf8');
  const lines = data.split(/\r?\n/);
    
  var x = lines[0];
  var y = lines[1];
  
  var cor = control_tempalte.Coordinates(x, y);
  var html = control_tempalte.HTML(cor);
  res.send(html);
  // res.sendFile(__dirname + '/control.html');
});
router.post('/control', (req, res, next) => {
  var x = req.body.control_x;
  var y = req.body.control_y;
  var description = `${x}\n${y}`;
  fs.writeFile(`html/coordinate`, description, 'utf8', function(err){ //여기서 적은걸로
    res.redirect('/default/control');  
  })
});

router.post('/answer', (req, res, next) => {
  var data = fs.readFileSync('html/coordinate', 'utf8');
  const lines = data.split(/\r?\n/);
    
  var x = lines[0];
  var y = lines[1];
  var text = `${x}\n${y}`;
  res.send(text);
});

router.get('/delete', (req, res, next) => {
  fsExtra.emptyDirSync('html/index');
  res.redirect('/default/control');  
});

router.post('/Fbx', (req, res, next) => {
  var fbxUrl = require("../Fbx/DoughNut_FBX.fbx");
  var fbxloader = new FBXLoader();
  fbxloader.load(fbxUrl, function(object){
    
  });
});



module.exports = router;
