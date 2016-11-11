var express = require('express');
var router = express.Router();
var mongoose = require('mongoose'), url = mongoose.model('Url');

/* GET home page. */
router.get('/', function(req, res, next) {
  res.render('index', { URL: '' });
});

router.post('/', function(req, res, next) {
    // get the tiny url
    
    
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
   console.log('the json', req.body.URL);
   res.render('index', req.body);
});

module.exports = router;