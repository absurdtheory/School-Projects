/***************************************************************************************
*  --SOURCE--
*    Title: main.js
*    Authors: Justin Wolford,Samarendra Hedao
*    Initial Publish Date: 10/25/2017
*    Availability: https://github.com/knightsamar/CS340-Sample-Web-App
***************************************************************************************/
var express = require('express');           //uses express
var mysql = require('./dbcon.js');          //connect to database
var bodyParser = require('body-parser')     //use body parser to parse form data

var app = express();                        
var path = require("path");                 //used for static html index page
var handlebars = require('express-handlebars').create({ defaultLayout: 'main' }); //uses express handlebars

app.engine('handlebars', handlebars.engine);
app.set('view engine', 'handlebars');
app.set('port', 5175);

app.use(bodyParser.json());
app.use(bodyParser.urlencoded({
    extended: true
}));

app.set('mysql', mysql);
app.use('/static', express.static('public'));   //used for css and js files

//use specific .js files to render each page and submit queries
app.use('/dogs', require('./dogs.js'));
app.use('/employees', require('./employees.js'));
app.use('/adopters', require('./adopters.js'));
app.use('/foodsupply', require('./foodsupply.js'));
app.use('/orders', require('./orders.js'));
app.use('/works', require('./works.js'));
app.use('/dogsearch', require('./search.js'));

app.use(express.static('public'));

//render index page
app.get('/index', function (req, res) {
    res.sendFile(path.join(__dirname+ '/views/index.html'));
});

//render home
app.get('/', function (req, res, next) {
    res.render('home');
});

//render 404 error page
app.use(function(req,res){
  res.status(404);
  res.render('404');
});

//render 500 error page
app.use(function(err, req, res, next){
  console.error(err.stack);
  res.status(500);
  res.render('500');
});

app.listen(app.get('port'), function(){
  console.log('Express started on http://localhost:' + app.get('port') + '; press Ctrl-C to terminate.');
});