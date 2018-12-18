// JavaScript source code
//listen to call validation function using the DOM
document.getElementById("btnAdopterSubmit").addEventListener("click", validateAdopterForm);

//function to perform client-side form validation and alerts the user of missing input
function validateAdopterForm() {
    var x = document.forms["addadopterform"]["fname"].value;
    var y = document.forms["addadopterform"]["lname"].value;
    var z = document.forms["addadopterform"]["saddress"].value;
    var a = document.forms["addadopterform"]["city"].value;
    var b = document.forms["addadopterform"]["state"].value;
    var c = document.forms["addadopterform"]["zip"].value;
    var d = document.forms["addadopterform"]["phone"].value;


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


}


/***************************************************************************************
*   function to delete an adopter, sends the adopters id to the server as a delete request
*  --SOURCE--
*    Title: deleteperson.js
*    Authors: Justin Wolford, Samarendra Hedao
*    Initial Publish Date: 10/25/2017
*    Code version: <code version>
*    Availability: https://github.com/knightsamar/CS340-Sample-Web-App/tree/master/public
***************************************************************************************/
function deleteAdopter(id) {
    $.ajax({
        url: '/adopters/' + id,
        type: 'DELETE',
        success: function (result) {
            window.location.reload(true);
        }
    })
};

