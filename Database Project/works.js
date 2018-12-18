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

    //function to call a mysql query to select the id and name of all dogs from the data base to populate the dropdown in the add form
    function getDogs(res, mysql, context, complete) {
        mysql.pool.query("SELECT id, name FROM Dogs", function (error, results, fields) {
            if (error) {
                res.write(JSON.stringify(error));
                res.end();
            }
            context.dogs = results; //define the results as "dogs"
            complete();             //call the complete function to increase callbackcount
        });
    }

    //function call a mysql query to select the id, first name, last name, and title of all employees to populate the dropdown in the add form
    function getEmployees(res, mysql, context, complete) {
        mysql.pool.query("SELECT id, fname, lname, title FROM Employees", function (error, results, fields) {
            if (error) {
                res.write(JSON.stringify(error));
                res.end();
            }
            context.employees = results; //define the results as "employees"
            complete();                  //call the complete function to increase callbackcount
        });
    }

    //function to call a mysql query to select all employee-dog relations in the works table, inner joins on Employees to get the first and last names, and title, and 
    //inner joins on Dogs to get the name of the dogs. Used to populate the Works page of existing relationships.
    function getWorks(res, mysql, context, complete) {
        mysql.pool.query("SELECT Employees.id as eid, fname, lname, title, Dogs.id as did, name FROM Employees INNER JOIN Works ON Employees.id = Works.EmployeeID INNER JOIN Dogs ON Dogs.id = Works.DogID", function (error, results, fields) {
            if (error) {
                res.write(JSON.stringify(error));
                res.end();
            }
            context.works = results;  //define the results as "works"
            complete();               //call the complete function to increase callbackcount
        });
    }

    //GET request to populate the "/works" page when initially loading, calls the appropriate functions to poplate the page
    router.get('/', function (req, res) {
        var callbackCount = 0;                              //used to keep track that all data from the database has been retrieved
        var context = {};                                   //holds the results
        var mysql = req.app.get('mysql');                   
        getDogs(res, mysql, context, complete);        
        getEmployees(res, mysql, context, complete);
        getWorks(res, mysql, context, complete);
        function complete() {                               //function to prevent the page from loading until all data has been retrieved
            callbackCount++;
            if (callbackCount >= 3) {
                res.render('works', context);
            }

        }
    });

    //POST request to insert data into the Works table
    router.post('/', function (req, res) {
        var mysql = req.app.get('mysql');
        var sql = "INSERT IGNORE INTO Works (EmployeeID, DogID) VALUES (?,?)";      //MySQL query to insert a relationship into the table (ignores duplicate entries)
        var inserts = [req.body.pid, req.body.did];                                 //holds the values being inserted
        sql = mysql.pool.query(sql, inserts, function (error, results, fields) {
            if (error) {
                console.log(JSON.stringify(error))
                res.write(JSON.stringify(error));
                res.end();
            } else {
                res.redirect('/works');                                             //reload the page
            }
        });
    });

   //DELETE request to delete data from the Works table, receives the EmployeeID and DogID from addWork.js
    router.delete('/EmployeeID/:EmployeeID/DogID/:DogID', function (req, res) {
        console.log(req.params.EmployeeID)
        console.log(req.params.DogID)
        var mysql = req.app.get('mysql');
        var sql = "DELETE FROM Works WHERE EmployeeID = ? AND DogID = ?";           //mySQL query to delete a relationship from the table
        var inserts = [req.params.EmployeeID, req.params.DogID];                    //holds the values representing the primary key of the relationship being deleted
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