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

    //function to select all information about employees to display on the employees page. Adds another row that translates the boolean fsa into "yes" or "no"
    function getEmployees(res, mysql, context, complete) {
        mysql.pool.query("SELECT id, fname, lname, fsa, phone, title, IF(fsa = 1, 'Yes', 'No') as auth FROM Employees ", function (error, results, fields) {
            if (error) {
                res.write(JSON.stringify(error));
                res.end();
            }
            context.employees = results;
            complete();
        });
    }

    //function to get one employee to prepopulate the employee edit page
    function getEmployee(res, mysql, context, id, complete) {
        var sql = "SELECT id, fname, lname, fsa, phone, title, IF(fsa = 1, 'Yes', 'No') as auth FROM Employees WHERE id = ?;";
        var inserts = [id];
        mysql.pool.query(sql, inserts, function (error, results, fields) {
            if (error) {
                res.write(JSON.stringify(error));
                res.end();
            }
            context.employee = results[0];
            complete();
        });
    }

    //GET request to render the /employees page when it loads, calls appropriate functions to populate page
    router.get('/', function (req, res) {
        var callbackCount = 0;
        var context = {};
        var mysql = req.app.get('mysql');
        getEmployees(res, mysql, context, complete);
        function complete() {
            callbackCount++;
            if (callbackCount >= 1) {
                res.render('employees', context);
            }

        }
    });

    //POST request to insert data into the employees table
    router.post('/', function (req, res) {
        if (req.body.fname != "" & req.body.lname != "" & req.body.phone != "" & req.body.title != "") {
            console.log(req.body)
            var mysql = req.app.get('mysql');
            var sql = "INSERT INTO Employees (fname, lname, fsa, phone, title) VALUES(?,?,?,?,?)";
            var inserts = [req.body.fname, req.body.lname, req.body.fsa, req.body.phone, req.body.title];
            sql = mysql.pool.query(sql, inserts, function (error, results, fields) {
                if (error) {
                    console.log(JSON.stringify(error))
                    res.write(JSON.stringify(error));
                    res.end();
                } else {
                    res.redirect('/employees');
                }
            });
        }
    });

    //DELETE request to delete data from the employees table, receives the id of the employee to be deleted from from addEmployee.js
    router.delete('/:id', function (req, res) {
        console.log(req.body);
        var mysql = req.app.get('mysql');
        var sql = "DELETE FROM Employees WHERE id = ?";
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

    //GET request gets the id of the employee being edited, calls the appropriate function, then renders the edit page with prepopulated data
    router.get('/:id', function (req, res) {
        callbackCount = 0;
        var context = {};
        context.jsscripts = ["updateEmployee.js"];
        var mysql = req.app.get('mysql');
        getEmployee(res, mysql, context, req.params.id, complete);
        function complete() {
            callbackCount++;
            if (callbackCount >= 1) {
                res.render('employeeedit', context);
            }

        }
    });

    //PUT request updates an employee with the information from the edit page and returns to the main employee page
    router.put('/:id', function (req, res) {
        var mysql = req.app.get('mysql');
        console.log(req.body)
        console.log(req.params)
        var sql = "UPDATE Employees SET fname = ?, lname = ?, fsa = ?, phone = ?, title = ? WHERE id = ?;"
        var inserts = [req.body.fname, req.body.lname, req.body.fsa, req.body.phone, req.body.title, req.params.id];
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
