// JavaScript source code
/***************************************************************************************
*   function that validates that all edit form input is correctly filled out, and if it
 *  is, sends a PUT request using jquery to the server with the id of the adopter being updated
*  --SOURCE (of PUT request)--
*    Title: updateperson.js
*    Authors: Justin Wolford, Samarendra Hedao
*    Initial Publish Date: 10/25/2017
*    Code version: <code version>
*    Availability: https://github.com/knightsamar/CS340-Sample-Web-App/tree/master/public
***************************************************************************************/
function updateAdopter(id) {
    var x = document.forms["editadopterform"]["fname"].value;
    var y = document.forms["editadopterform"]["lname"].value;
    var z = document.forms["editadopterform"]["saddress"].value;
    var a = document.forms["editadopterform"]["city"].value;
    var b = document.forms["editadopterform"]["state"].value;
    var c = document.forms["editadopterform"]["zip"].value;
    var d = document.forms["editadopterform"]["phone"].value;


    if (x == "") {
        alert("First Name must be filled out");
        return false;
    }
    else if (y == "") {
        alert("Last Name must be filled out");
        return false;
    }
    else if (z == "") {
        alert("Street Address must be filled out");
        return false;
    }
    else if (a == "") {
        alert("City must be filled out");
        return false;
    }
    else if (b == "") {
        alert("State must be filled out");
        return false;
    }
    else if (c == "") {
        alert("Zipcode must be filled out");
        return false;
    }
    else if (d == "") {
        alert("Phone Number must be filled out");
        return false;
    }
    else {
        $.ajax({
            url: '/adopters/' + id,
            type: 'PUT',
            data: $('#editadopterform').serialize(),
            success: function (result) {
                window.location.replace("./");
            }
        })
    }
};