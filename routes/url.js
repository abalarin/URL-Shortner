var express = require('express');
var router = express.Router();

var mongoose = require('mongoose'), url = mongoose.model('Url');

/* GET users listing. */
router.get('/', function(req, res, next) {
    var db = req.db;
    url.find({},{},function(e, data){
        res.render('urllist', {"urllist" : data});
    });
});

module.exports = router;