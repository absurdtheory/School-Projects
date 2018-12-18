// JavaScript source code
/***************************************************************************************
*   function that validates that all edit form input is correctly filled out, and if it
 *  is, sends a PUT request using jquery to the server with the id of the food being updated
*  --SOURCE (of PUT request)--
*    Title: updateperson.js
*    Authors: Justin Wolford, Samarendra Hedao
*    Initial Publish Date: 10/25/2017
*    Code version: <code version>
*    Availability: https://github.com/knightsamar/CS340-Sample-Web-App/tree/master/public
***************************************************************************************/
function updateFood(id) {

    var x = document.forms["editfoodsupplyform"]["bname"].value;
    var y = document.forms["editfoodsupplyform"]["pname"].value;
    var z = document.forms["editfoodsupplyform"]["amount"].value;

    if (x == "") {
        alert("Brand Name must be filled out");
        return false;
    }
    else if (y == "") {
        alert("Product must be filled out");
        return false;
    }
    else if (z < 0) {
        alert("Quantity must be zero or greater")
    }
    else {
        $.ajax({
            url: '/foodsupply/' + id,
            type: 'PUT',
            data: $('#editfoodsupplyform').serialize(),
            success: function (result) {
                window.location.replace("./");
            }
        })
    }
};