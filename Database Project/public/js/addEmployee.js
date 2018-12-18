//listen to call validation function using the DOM
document.getElementById("btnEmployeesSubmit").addEventListener("click", validateEmployeeForm);

//function to validate all required input has been filled out
function validateEmployeeForm() {
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


}

/***************************************************************************************
*   function to delete an an employee, sends the employee's id to the server as a delete request
*  --SOURCE--
*    Title: deleteperson.js
*    Authors: Justin Wolford, Samarendra Hedao
*    Initial Publish Date: 10/25/2017
*    Code version: <code version>
*    Availability: https://github.com/knightsamar/CS340-Sample-Web-App/tree/master/public
***************************************************************************************/
function deleteEmployee(id) {
    $.ajax({
        url: '/employees/' + id,
        type: 'DELETE',
        success: function (result) {
            window.location.reload(true);
        }
    })
};