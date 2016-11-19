var express = require('express');
var router = express.Router();

//require the Twilio module and create a REST client
var accountSid = 'ACea45b8f40c69d717e0b0c31d62b5f3e9';
var authToken = 'c90bc2bbb89615700d63aa53cc96b03b';

var client = require('twilio')(accountSid, authToken);
function shorten(longURL){
  var hash = '';
  for (i=0; i < 3; i++){
    var rand = Math.floor((Math.random() * (longURL.length-1)) + 1);
    hash = hash + longURL[rand];
  }
  return hash;
}

/* GET home page. */
router.get('/', function(req, res, next) {
  res.render('index', { URL: '' });
});

router.post('/', function(req, res, next) {
  //doing a 64 base encoding proc on entered URL
  var url = req.body.URL;
  var encoded = new Buffer(url).toString('base64');


  //Storing encoded url into JSON and passing it to html page.
  // next step: shorten encoding probably using some bit shiffting
  // and padding ends to fit in 3 char key.
  url64 = 'www.example.com/' + shorten(encoded);
  enc = {URL : url64}

/* ----MONGODB STUFF-----
    // create a new object to store in the database
    var newUrl = new url();
    newUrl.url = req.body.URL;
    // this should be the tiny URL
    newUrl.tiny_url = req.body.URL;

    // save the object to the DB and report any error
    newUrl.save(function (error){
        if (error){
            throw(error);
        } else {
            console.log("Success!");
        }
    });
    ------end-----------*/

   res.render('index', enc);

});

function send(){
  client.messages.create({
      to: "+12103808155",
      from: "+12015741835",
      body: "This is the ship that made the Kessel Run in fourteen parsecs?",
  }, function(err, message) {
      console.log(message.sid);
  });
}

module.exports = router;
