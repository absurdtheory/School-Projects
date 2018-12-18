// JavaScript source code
/***************************************************************************************
*  --SOURCE--
*    Title: people_certs.js
*    Authors: Samarendra Hedao
*    Initial Publish Date: 03/15/2018
*    Availability: https://github.com/knightsamar/CS340-Sample-Web-App
***************************************************************************************/
module.exports = function () {
    var express = require('express');
    var router = express.Router();

    //function to call a mysql query to select the id and first and last names of all employees authorized to order frood from the database to populate the dropdown in the add form
    function getEmployees(res, mysql, context, complete) {
        mysql.pool.query("SELECT id, fname, lname FROM Employees WHERE fsa = TRUE", function (error, results, fields) {
            if (error) {
                res.write(JSON.stringify(error));
                res.end();
            }
            context.employee = results;     //define results as "employee"
            complete();                     //call the complete function to increase callbackcount
        });
    }

    //function call a mysql query to select the id, brand name, and product name all food types to populate the dropdown in the add form
    function getFood(res, mysql, context, complete) {
        mysql.pool.query("SELECT id, bname, pname FROM FoodSupply", function (error, results, fields) {
            if (error) {
                res.write(JSON.stringify(error));
                res.end();
            }
            context.food = results;         //define results as "food"
            complete();                     //call the complete function to increase callbackcount
        });
    }

    //function to call a mysql query to select all food supply-employee-datetime relations in the Orders table. Selects employees id, first name, and last name from Employees, then inner
    //joins on Orders to only get those who have ordered food and quantity of food ordered, then Inner joins on Food Supply to get the brand name, and product names of the food ordered
    function getOrders(res, mysql, context, complete) {
        mysql.pool.query("SELECT Employees.id as eid, fname, lname, FoodSupply.id as fid, bname, pname, Orders.quantity, DATE_FORMAT(dateOrdered, '%Y-%m-%d %H:%i:%s') AS newDate FROM Employees INNER JOIN Orders ON Employees.id = Orders.EmployeeID INNER JOIN FoodSupply ON FoodSupply.id = Orders.FoodSupplyID ORDER BY Orders.dateOrdered", function (error, results, fields) {
            if (error) {
                res.write(JSON.stringify(error));
                res.end();
            }
            context.order = results;        //define results as "order"
            complete();                     //call the complete function to increase callbackcount
        });
    }

    //GET request to populate the "/orders" page when initially loading, calls the appropriate functions to poplate the page
    router.get('/', function (req, res) {
        var callbackCount = 0;                          //used to keep track that all data from the database has been retrieved
        var context = {};                               //holds the results
        var mysql = req.app.get('mysql');
        getEmployees(res, mysql, context, complete);
        getFood(res, mysql, context, complete);
        getOrders(res, mysql, context, complete);
        function complete() {                             //function to prevent the page from loading until all data has been retrieved
            callbackCount++;
            if (callbackCount >= 3) {
                res.render('orders', context);
            }
        }
    });

    //POST request to insert data into the Orders table
    router.post('/', function (req, res) {
        if (req.body.quantity != "" & req.body.quantity > 0) {
            var mysql = req.app.get('mysql');
            var sql = "INSERT INTO Orders (FoodSupplyID, EmployeeID, quantity) VALUES (?,?,?)";  //MySQL query to insert a relationship into the table
            var inserts = [req.body.food, req.body.pid, req.body.quantity];                      //holds the values being inserted
            sql = mysql.pool.query(sql, inserts, function (error, results, fields) {
                if (error) {
                    console.log(JSON.stringify(error))
                    res.write(JSON.stringify(error));
                    res.end();
                } else {
                    res.redirect('/orders');                                                    //reload the page
                }
            });
        }
    });

    //DELETE request to delete data from the Orders table, receives the Food SupplyID, EmployeeID and DateOrdered from addOrder.js
    router.delete('/FoodSupplyID/:FoodSupplyID/EmployeeID/:EmployeeID/DateOrdered/:dateOrdered', function (req, res) {
        console.log(req.params.FoodSupplyID);
        console.log(req.params.EmployeeID);
        console.log(req.params.dateOrdered);
        var mysql = req.app.get('mysql');
        var sql = "DELETE FROM Orders WHERE FoodSupplyID = ? AND EmployeeID = ? AND DateOrdered = ?";       //mySQL query to delete a relationship from the table
        var inserts = [req.params.FoodSupplyID, req.params.EmployeeID, req.params.dateOrdered];             //holds the values representing the primary key of the relationship being deleted
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


    return router;
}();
