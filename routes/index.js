var express = require('express');
var router = express.Router();

/* GET home page. */
router.get('/', function(req, res, next) {
  res.render('index');
});

router.post('/', function(req, res, next) {
  //console.log('the json', req.body);

  //doing a 64 base encoding proc on entered URL
  var url = req.body.URL;
  var encoded = new Buffer(url).toString('base64');

  //Storing encoded url into JSON and passing it to html page.
  // next step: shorten encoding probably using some bit shiffting
  // and padding ends to fit in 3 char key.
  url64 = 'www.example.com/' + encoded;
  enc = {URL : url64}
  res.render('index', enc);
});

module.exports = router;
