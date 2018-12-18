// JavaScript source code
/***************************************************************************************
*  --SOURCE--
*    Title: people.js
*    Authors: Justin, Wolford, Samarendra Hedao
*    Initial Publish Date: 10/25/2017
*    Availability: https://github.com/knightsamar/CS340-Sample-Web-App
***************************************************************************************/
module.exports = function () {
    var express = require('express');
    var router = express.Router();

    //function to call a mysql query to select the id, name, birthdate, breed, sex, adoptedBy, foodType, and image from dogs, left joins on adopters to get first and last names of adopter (or null)
    //if no adopter and inner joins on Food Supply to get the brand name and product name of the foodType
    function getDogs(res, mysql, context, complete) {
        mysql.pool.query("SELECT d.id, name, DATE_FORMAT(birthdate, '%m-%d-%Y') as bdate, breed, sex, adoptedBy, foodType, image, a.fname, a.lname, f.bname, f.pname FROM Dogs d LEFT JOIN Adopters a ON d.adoptedBy = a.id INNER JOIN FoodSupply f ON d.foodType = f.id ORDER BY d.id", function (error, results, fields) {
            if (error) {
                res.write(JSON.stringify(error));
                res.end();
            }
            context.dogs = results;     //define the results as "dogs"
            complete();                 //call the complete function to increase callbackcount
        });
    }

    //function to call a mysql query to select the id, brand name, and product name of all food from the database to populate the dropdown in the search form
    function getFood(res, mysql, context, complete) {
        mysql.pool.query("SELECT id, bname, pname FROM FoodSupply", function (error, results, fields) {
            if (error) {
                res.write(JSON.stringify(error));
                res.end();
            }
            context.food = results;
            complete();
        });
    }

    //function to call a mysql query to select the id, first name, and last name of all adopters from the database to populate the dropdown in the search form
    function getAdopters(res, mysql, context, complete) {
        mysql.pool.query("SELECT id, fname, lname FROM Adopters", function (error, results, fields) {
            if (error) {
                res.write(JSON.stringify(error));
                res.end();
            }
            context.adopter = results;
            complete();
        });

    }

    //function to select dogs that match the search parameters, modifies the query based on what is selected/entered
    //source: https://love2dev.com/blog/javascript-remove-from-array/
    function dogSearch(req, res, mysql, context, complete) {

        //begining part of the query that selects everything that needs to be displayed
        var query = "SELECT d.id, name, DATE_FORMAT(birthdate, '%m-%d-%Y') as bdate, breed, sex, adoptedBy, foodType, image, a.fname, a.lname, f.bname, f.pname FROM Dogs d LEFT JOIN Adopters a ON d.adoptedBy = a.id INNER JOIN FoodSupply f ON d.foodType = f.id ";
        var inserts = [req.params.name, req.params.birthdate, req.params.breed, req.params.food, req.params.sex, req.params.adopter]; //holds the variables to be used to select dogs based on searchDogs.js

        //WHERE portion of query
        //adjusts if name is a parameter, if the user does not enter a name, removes that parameter from inserts
        if (req.params.name != "none") {
            var name1 = "WHERE d.name = ? AND "
        }
        else {
            name1 = "WHERE ";

            for (var i = 0; i < inserts.length - 1; i++) {
                if (inserts[i] === req.params.name) {
                    inserts.splice(i, 1);
                }
            }
        }

        //adjusts if birthdate is a parameter, if the user does not enter a birthdate, removes that parameter from inserts
        if (req.params.birthdate != "none") {
            var bdate = "d.birthdate = ? AND "
        }
        else {
            bdate = "";
            for (var i = 0; i < inserts.length - 1; i++) {
                if (inserts[i] === req.params.birthdate) {
                    inserts.splice(i, 1);
                }
            }
        }

        //adjusts if breed is a parameter, if the user does not enter a breed, removes that parameter from inserts
        if (req.params.breed != "none") {
            var breed1 = "d.breed = ? AND "
        }
        else {
            breed1 = "";
            for (var i = 0; i < inserts.length - 1; i++) {
                if (inserts[i] === req.params.breed) {
                    inserts.splice(i, 1);
                }
            }
        }

        //adjusts the food parameter, if the user chooses any food, selects dogs with any food type (matching the other parameters)
        if (req.params.food == "any") {
            var food1 = "d.foodType = d.foodType "

            for (var i = 0; i < inserts.length - 1; i++) {
                if (inserts[i] === req.params.food) {
                    inserts.splice(i, 1);
                }
            }
        }
        else {
            food1 = "d.foodType = ? "
        }

        //adjusts the sex parameter, if the user chooses all sexes, selects dogs regardless of sex (matching the other parameters)
        if (req.params.sex == "All") {
            var sex1 = "AND d.sex = ANY (SELECT sex FROM Dogs) "

            for (var i = 0; i < inserts.length - 1; i++) {
                if (inserts[i] === req.params.sex) {
                    inserts.splice(i, 1);
                }
            }
        }
        else {
            sex1 = "AND d.sex = ? "
        }

        //adjusts the food parameter, if the user chooses either, selects dogs with or without an adopter, if the user chooses any, selects dogs with any adopters,
        //if the user chooses "NULL" selects dogs without adopters (matching the other parameters)
        if (req.params.adopter == "either") {
            var adopter1 = "";

            for (var i = 0; i < inserts.length - 1; i++) {
                if (inserts[i] === req.params.adopter) {
                    inserts.splice(i, 1);
                }
            }
        }
        else if (req.params.adopter == "any") {
            adopter1 = "AND d.adoptedBy = ANY (SELECT adoptedBy FROM Dogs) ORDER BY d.id";

            for (var i = 0; i < inserts.length - 1; i++) {
                if (inserts[i] === req.params.adopter) {
                    inserts.splice(i, 1);
                }
            }
        }
        else if (req.params.adopter == "NULL") {
            adopter1 = "AND d.adoptedBy IS NULL ORDER BY d.id";

            for (var i = 0; i < inserts.length - 1; i++) {
                if (inserts[i] === req.params.adopter) {
                    inserts.splice(i, 1);
                }
            }
        }
        else {
            adopter1 = "AND d.adoptedBy = ? ORDER BY d.id;";
        }

        query = query + name1 + bdate + breed1 + food1 + sex1 + adopter1;   //put together the entire query into one string
        console.log(req.params);
        mysql.pool.query(query, inserts, function (error, results, fields) {
            if (error) {
                res.write(JSON.stringify(error));
                res.end();
            }
            console.log(results)
            context.dogs = results;         //define the results as dogs
            complete();                     //call the complete function to increase callbackcount
        });
    }

    //GET request to populate the "/dogsearch" page when initially loading, calls the appropriate functions to poplate the page
    router.get('/', function (req, res) {
        var callbackCount = 0;                      //used to keep track that all data from the database has been retrieved
        var context = {};                           //holds the results
        var mysql = req.app.get('mysql');
        getDogs(res, mysql, context, complete);
        getFood(res, mysql, context, complete);
        getAdopters(res, mysql, context, complete);
        function complete() {                         //function to prevent the page from loading until all data has been retrieved
            callbackCount++;
            if (callbackCount >= 3) {
                res.render('dogsearch', context);
            }

        }
    });

    //GET request to populate the page with the search results
    router.get('/:name/:birthdate/:breed/:food/:sex/:adopter', function (req, res) {
        var callbackCount = 0;
        var context = {};
        context.jsscripts = ["searchDogs.js"];          //retrieves information about search from searchDogs.js
        var mysql = req.app.get('mysql');
        dogSearch(req, res, mysql, context, complete);
        getFood(res, mysql, context, complete);
        getAdopters(res, mysql, context, complete);
        function complete() {
            callbackCount++;
            if (callbackCount >= 3) {
                res.render('dogsearch', context);
            }

        }
    });

    return router;
}();
