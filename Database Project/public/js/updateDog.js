// JavaScript source code
/***************************************************************************************
*   function that validates that all edit form input is correctly filled out, and if it
 *  is, sends a PUT request using jquery to the server with the id of the dog being updated
*  --SOURCE (of PUT request)--
*    Title: updateperson.js
*    Authors: Justin Wolford, Samarendra Hedao
*    Initial Publish Date: 10/25/2017
*    Code version: <code version>
*    Availability: https://github.com/knightsamar/CS340-Sample-Web-App/tree/master/public
***************************************************************************************/
function updateDog(id) {
    var x = document.forms["editdogform"]["name"].value;
    var y = document.forms["editdogform"]["birthdate"].value;
    var z = document.forms["editdogform"]["breed"].value;

    if (x == "") {
        alert("Name must be filled out");
        return false;
    }
    else if (y == "") {
        alert("Birthdate must be entered");
        return false;
    }
    else if (z == "") {
        alert("Breed must be filled out");
        return false;
    }
    else {
        $.ajax({
            url: '/dogs/' + id,
            type: 'PUT',
            data: $('#editdogform').serialize(),
            success: function (result) {
                window.location.replace("./");
            }
        })
    }
};