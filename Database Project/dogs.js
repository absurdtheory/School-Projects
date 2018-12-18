// JavaScript source code
/***************************************************************************************
*  --SOURCE--
*    Title: people.js
*    Authors: Justin Wolford,Samarendra Hedao
*    Initial Publish Date: 10/25/2017
*    Availability: https://github.com/knightsamar/CS340-Sample-Web-App
***************************************************************************************/
module.exports = function () {
    var express = require('express');
    var router = express.Router();

    //function to select all information about dogs to display on the manage dogs page, left joins on adopters to get their first and last name if there is one (blank if not)
    //and inner joins on food supply to get the brand name and product name
    function getDogs(res, mysql, context, complete) {
        mysql.pool.query("SELECT d.id, name, DATE_FORMAT(birthdate, '%m-%d-%Y') as bdate, breed, sex, adoptedBy, foodType, image, a.fname, a.lname, f.bname, f.pname FROM Dogs d LEFT JOIN Adopters a ON d.adoptedBy = a.id INNER JOIN FoodSupply f ON d.foodType = f.id ORDER BY d.id", function (error, results, fields) {
            if (error) {
                res.write(JSON.stringify(error));
                res.end();
            }
            context.dogs = results;
            complete();
        });
    }

    //function to select one dog to prepopulate the edit page
    function getDog(res, mysql, context, id, complete) {
        var sql = "SELECT d.id, name, DATE_FORMAT(birthdate, '%Y-%m-%d') as bdate, breed, sex, adoptedBy, foodType, image, a.fname, a.lname, f.bname, f.pname FROM Dogs d LEFT JOIN Adopters a ON d.adoptedBy = a.id INNER JOIN FoodSupply f ON d.foodType = f.id WHERE d.id = ?;";
        var inserts = [id];
        mysql.pool.query(sql, inserts, function (error, results, fields) {
            if (error) {
                res.write(JSON.stringify(error));
                res.end();
            }
            context.dog = results[0];
            complete();
        });
    }

    //function to select all food to autopopulate the dropdown in the add form
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

    //function to select all adopters to autopopulate the dropdown in the add form
    function getAdopters(req, mysql, context, complete) {
        mysql.pool.query("SELECT id, fname, lname FROM Adopters", function (error, results, fields) {
            if (error) {
                res.write(JSON.stringify(error));
                res.end();
            }
            context.adopters = results;
            complete();
        });
    }

    //GET request to render the /dogs page when it loads, calls appropriate functions to populate page
    router.get('/', function (req, res) {
        var callbackCount = 0;
        var context = {};
        var mysql = req.app.get('mysql');
        getDogs(res, mysql, context, complete);
        getFood(res, mysql, context, complete);
        function complete() {
            callbackCount++;
            if (callbackCount >= 2) {
                res.render('dogs', context);
            }

        }
    });

    //POST request to insert data into the dogs table
    router.post('/', function (req, res) {
        if (req.body.name != "" & req.body.birthdate != "" & req.body.breed != "" & req.body.sex != "") {
            console.log(req.body);
            var mysql = req.app.get('mysql');

            var sql = "INSERT INTO Dogs(name, birthdate, breed, sex, foodType, image) VALUES(?,?,?,?,?,?)";
            var inserts = [req.body.name, req.body.birthdate, req.body.breed, req.body.sex, req.body.food, req.body.image];
            sql = mysql.pool.query(sql, inserts, function (error, results, fields) {
                if (error) {
                    console.log(JSON.stringify(error))
                    res.write(JSON.stringify(error));
                    res.end();
                } else {
                    res.redirect('/dogs');
                }
            });
        }
        else {
            console.log("All information must be filled out")
        }
    });

    //DELETE request to delete data from the Dogs table, receives the id of the dog to be deleted from from addDog.js
    router.delete('/:id', function (req, res) {
        console.log(req.body);
        var mysql = req.app.get('mysql');
        var sql = "DELETE FROM Dogs WHERE id = ?";
        var inserts = [req.body.id];
        sql = mysql.pool.query(sql, inserts, function (error, results, fields) {
            if (error) {
                res.write(JSON.stringify(error));
                res.status(400);
                res.end();
            } else {
                res.status(202).end();
            }
        })
    })

    //GET request gets the id of the dog being edited, calls the appropriate function, then renders the edit page with prepopulated data
    router.get('/:id', function (req, res) {
        callbackCount = 0;
        var context = {};
        context.jsscripts = ["updateDog.js"];
        var mysql = req.app.get('mysql');
        getDog(res, mysql, context, req.params.id, complete);
        getFood(res, mysql, context, complete);
        getAdopters(res, mysql, context, complete)
        function complete() {
            callbackCount++;
            if (callbackCount >= 3) {
                res.render('dogedit', context);
            }

        }
    });

    //PUT request updates a dog with the information from the edit page and returns to the main dog page
    router.put('/:id', function (req, res) {
        var mysql = req.app.get('mysql');
        console.log(req.body)
        console.log(req.params)
        //if there is an adopter
        if (req.body.adoptedBy != '') {
            var sql = "UPDATE Dogs SET name = ?, birthdate = ?, breed = ?, sex = ?, adoptedBy = ?, foodType = ?, image = ? WHERE id = ?;"
            var inserts = [req.body.name, req.body.birthdate, req.body.breed, req.body.sex, req.body.adoptedBy, req.body.foodType, req.body.image, req.params.id];
            sql = mysql.pool.query(sql, inserts, function (error, results, fields) {
                if (error) {
                    console.log(error)
                    res.write(JSON.stringify(error));
                    res.end();
                } else {
                    res.status(200);
                    res.end();
                }
            });
        }//else set adopter to NULL
        else {
            var sql = "UPDATE Dogs SET name = ?, birthdate = ?, breed = ?, sex = ?, adoptedBy = NULL, foodType = ?, image = ? WHERE id = ?;"
            var inserts = [req.body.name, req.body.birthdate, req.body.breed, req.body.sex, req.body.foodType, req.body.image, req.params.id];
            sql = mysql.pool.query(sql, inserts, function (error, results, fields) {
                if (error) {
                    console.log(error)
                    res.write(JSON.stringify(error));
                    res.end();
                } else {
                    res.status(200);
                    res.end();
                }
            });
        }
        
    });

    return router;
}();
