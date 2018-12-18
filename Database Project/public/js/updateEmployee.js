// JavaScript source code
/***************************************************************************************
*   function that validates that all edit form input is correctly filled out, and if it
 *  is, sends a PUT request using jquery to the server with the id of the employee being updated
*  --SOURCE (of PUT request)--
*    Title: updateperson.js
*    Authors: Justin Wolford, Samarendra Hedao
*    Initial Publish Date: 10/25/2017
*    Code version: <code version>
*    Availability: https://github.com/knightsamar/CS340-Sample-Web-App/tree/master/public
***************************************************************************************/
function updateEmployee(id) {
    var x = document.forms["editemployeeform"]["fname"].value;
    var y = document.forms["editemployeeform"]["lname"].value;
    var z = document.forms["editemployeeform"]["phone"].value;
    var s = document.forms["editemployeeform"]["title"].value;

    if (x == "") {
        alert("First Name must be filled out");
        return false;
    }
    else if (y == "") {
        alert("Last Name must be filled out");
        return false;
    }
    else if (z == "") {
        alert("Phone number must be filled out");
        return false;
    }
    else if (s == "") {
        alert("Job Title must be filled out");
        return false;
    }
    else {
        $.ajax({
            url: '/employees/' + id,
            type: 'PUT',
            data: $('#editemployeeform').serialize(),
            success: function (result) {
                window.location.replace("./");
            }
        })
    }
};