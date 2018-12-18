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

    //function to select food to populate the Food Supply page. Selects the id, brand name, product name, and amount from Food Supply, and left joins on Dogs to COUNT() the 
    //number of dogs on each food .
    function getFood(res, mysql, context, complete) {
        mysql.pool.query("SELECT f.id, bname, pname, COUNT(d.id) AS numberd, amount FROM FoodSupply f LEFT JOIN Dogs d ON f.id = d.foodType GROUP BY f.id", function (error, results, fields) {
            if (error) {
                res.write(JSON.stringify(error));
                res.end();
            }
            context.food = results; //define the results as food
            complete();             //call the complete function to increase callbackcount
        });
    }

    //function to select one food to edit
    function getOneFood(res, mysql, context, id, complete) {
        var sql = "SELECT id, bname, pname, amount FROM FoodSupply WHERE id = ?;";
        var inserts = [id];
        mysql.pool.query(sql, inserts, function (error, results, fields) {
            if (error) {
                res.write(JSON.stringify(error));
                res.end();
            }
            context.food = results[0];  //define the result as food
            complete();                 //call the complete function to increase callbackcount
        });
    }

    //GET request to render the /foodsupply page when the loads, calls appropriate functions to populate page
    router.get('/', function (req, res) {
        var callbackCount = 0;
        var context = {};
        var mysql = req.app.get('mysql');
        getFood(res, mysql, context, complete);
        function complete() {
            callbackCount++;
            if (callbackCount >= 1) {
                res.render('foodsupply', context);
            }

        }
    });

    //POST request to insert data into the Food Supply table
    router.post('/', function (req, res) {
        console.log(req.body)
        var mysql = req.app.get('mysql');

        var sql = "INSERT INTO FoodSupply (bname, pname) VALUES(?,?)";
        var inserts = [req.body.bname, req.body.pname];
        sql = mysql.pool.query(sql, inserts, function (error, results, fields) {
            if (error) {
                console.log(JSON.stringify(error))
                res.write(JSON.stringify(error));
                res.end();
            } else {
                res.redirect('/foodsupply');
            }
        });
    });

    //DELETE request to delete data from the FoodSupply table, receives the id of the food to be deleted from from addFood.js
    router.delete('/:id', function (req, res) {
        var mysql = req.app.get('mysql');
        var sql = "DELETE FROM FoodSupply WHERE id = ?";
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

    //GET request gets the id of the food being edited, calls the appropriate function, then renders the edit page with prepopulated data
    router.get('/:id', function (req, res) {
        callbackCount = 0;
        var context = {};
        context.jsscripts = ["updateFoodSupply.js"];
        var mysql = req.app.get('mysql');
        getOneFood(res, mysql, context, req.params.id, complete);
        function complete() {
            callbackCount++;
            if (callbackCount >= 1) {
                res.render('foodsupplyedit', context);
            }

        }
    });

    //PUT request updates a food with the information from the edit page and returns to the main food supply page
    router.put('/:id', function (req, res) {
        var mysql = req.app.get('mysql');
        console.log(req.body)
        console.log(req.params)
        var sql = "UPDATE FoodSupply SET bname = ?, pname = ?, amount = ? WHERE id = ?;"
        var inserts = [req.body.bname, req.body.pname, req.body.amount, req.params.id];
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