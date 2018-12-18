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

    //function to select adopters to populate the adopter page. Selects all information from adopters, and LEFT JOINS on dogs to calculate the number of dogs
    //each adopter has adopted using COUNT()
    function getAdopters(res, mysql, context, complete) {
        mysql.pool.query("SELECT Adopters.id, fname, lname, saddress, city, state, zip, phone, COUNT(d.id) as nad FROM Adopters LEFT JOIN Dogs d ON Adopters.id = d.adoptedBy GROUP BY Adopters.id",
            function (error, results, fields) {
            if (error) {
                res.write(JSON.stringify(error));
                res.end();
            }
            context.adopters = results;     //define results as "adopters"
            complete();                     //call the complete function to increase callbackcount
        });
    }

    //function to select one adopter prepopulate the edit page
    function getAdopter(res, mysql, context, id, complete) {
        var sql = "SELECT Adopters.id, fname, lname, saddress, city, state, zip, phone FROM Adopters WHERE Adopters.id = ?";
        var inserts = [id];
        mysql.pool.query(sql, inserts, function (error, results, fields) {
            if (error) {
                res.write(JSON.stringify(error));
                res.end();
            }
            context.adopter = results[0];   //define result as "adopter"
            complete();                     //call the complete function to increase callbackcount
        });
    }

    //GET request to render the /adopters page when it loads, calls appropriate functions to populate page
    router.get('/', function (req, res) {
        var callbackCount = 0;
        var context = {};
        var mysql = req.app.get('mysql');
        getAdopters(res, mysql, context, complete);
        function complete() {
            callbackCount++;
            if (callbackCount >= 1) {
                res.render('adopters', context);
            }

        }
    });

    //POST request to insert data into the adopters table
    router.post('/', function (req, res) {
        if (req.body.fname != "" & req.body.lname != "" & req.body.saddress != "" & req.body.city != "" & req.body.state != "" & req.body.zip != "" & req.body.phone != "") {
            console.log(req.body)
            var mysql = req.app.get('mysql');
            var sql = "INSERT INTO Adopters (fname, lname, saddress, city, state, zip, phone) VALUES(?,?,?,?,?,?,?)";
            var inserts = [req.body.fname, req.body.lname, req.body.saddress, req.body.city, req.body.state, req.body.zip, req.body.phone];
            sql = mysql.pool.query(sql, inserts, function (error, results, fields) {
                if (error) {
                    console.log(JSON.stringify(error))
                    res.write(JSON.stringify(error));
                    res.end();
                } else {
                    res.redirect('/adopters');
                }
            });
        }
    });

    //DELETE request to delete data from the Adopter table, receives the id of the adopter to be deleted from from addAdopter.js
    router.delete('/:id', function (req, res) {
        var mysql = req.app.get('mysql');
        var sql = "DELETE FROM Adopters WHERE id = ?";
        var inserts = [req.params.id];
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

    //GET request gets the id of the adopter being edited, calls the appropriate function, then renders the edit page with prepopulated data
    router.get('/:id', function (req, res) {
        callbackCount = 0;
        var context = {};
        var mysql = req.app.get('mysql');
        getAdopter(res, mysql, context, req.params.id, complete);
        function complete() {
            callbackCount++;
            if (callbackCount >= 1) {
                res.render('adopteredit', context);
            }

        }
    });

    //PUT request updates an adopter with the information from the edit page and returns to the main adopter page
    router.put('/:id', function (req, res) {
        var mysql = req.app.get('mysql');
        console.log(req.body)
        console.log(req.params.id)
        var sql = "UPDATE Adopters SET fname = ?, lname = ?, saddress = ?, city = ?, state = ?, zip = ?, phone = ? WHERE id = ?;"
        var inserts = [req.body.fname, req.body.lname, req.body.saddress, req.body.city, req.body.state, req.body.zip, req.body.phone, req.params.id];
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
    });

    return router;
}();
