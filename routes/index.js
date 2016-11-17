var base62 = ['0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z']
console.log(base62.length);
  var s = 'asjdnfjasnrjl4r';
  var hv = 0;
  for (var i = 0; i < s.length; i++){
    console.log(s[i] +' : ' +s[i].charCodeAt(0));
    hv = (127 * hv + s[i]) % 16908799;
  }
  console.log(hv);


/* GET home page. */
router.get('/', function(req, res, next) {
  res.render('index', { URL: '' });
});

router.post('/', function(req, res, next) {
// <<<<<<< HEAD
//   //console.log('the json', req.body);
//
//   //doing a 64 base encoding proc on entered URL
//   var url = req.body.URL;
//   base62(url);
//   var encoded = new Buffer(url).toString('base64');
//   var url = parseInt(encoded, 10);
//   //console.log(encoded);
//   //var shorten = new Buffer(url).toString('base64');
//   console.log(encoded);
//   console.log(base10);
//   for (i=0; i < encoded.length; i++){
//     var c = encoded[i];
//   }
//
//
//   //Storing encoded url into JSON and passing it to html page.
//   // next step: shorten encoding probably using some bit shiffting
//   // and padding ends to fit in 3 char key.
//   //shorten = encoded.trunc(5)
//   //console.log(shorten);
//   url64 = 'www.example.com/' + encoded;
//   enc = {URL : url64}
//   res.render('index', enc);
// });
//
// function base10(){
//
// }
// module.exports = router;
// =======
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
