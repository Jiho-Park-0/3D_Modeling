var express = require('express');
var router = express.Router();

router.get('/', (req, res, next) => res.sendFile(__dirname + '/main.html'));
router.post('/', (req, res, next) => {
    
})

router.get('/list', (req, res, next) => res.sendFile(__dirname + '/list.html'));
router.post('/list', (req, res, next) => {
    
})

router.get('/modeling', (req, res, next) => res.sendFile(__dirname + '/modeling.html'));
router.post('/modeling', (req, res, next) => {
    
})

module.exports = router;