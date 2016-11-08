var express = require('express');
var router = express.Router();

/* GET home page. */
router.get('/', function(req, res, next) {
  res.render('index', { URL: 'sample' });
});

router.post('/', function(req, res, next) {
  console.log('the json', req.body);
  res.render('index', req.body);
});

module.exports = router;
