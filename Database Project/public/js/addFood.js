//listen to call validation function using the DOM
document.getElementById("submitFoodBtn").addEventListener("click", validateFoodForm);

//function to validate the form has been filled out properly
function validateFoodForm() {
    var x = document.forms["addfoodform"]["bname"].value;
    var y = document.forms["addfoodform"]["pname"].value;

    if (x == "") {
        alert("Brand Name must be filled out");
        return false;
    }
    else if (y == "") {
        alert("Product must be filled out");
        return false;
    }


}

/***************************************************************************************
*   function to delete an a food, sends the food's id to the server as a delete request
*  --SOURCE--
*    Title: deleteperson.js
*    Authors: Justin Wolford, Samarendra Hedao
*    Initial Publish Date: 10/25/2017
*    Code version: <code version>
*    Availability: https://github.com/knightsamar/CS340-Sample-Web-App/tree/master/public
***************************************************************************************/
function deleteFood(id) {
    $.ajax({
        url: '/foodsupply/' + id,
        type: 'DELETE',
        success: function (result) {
            window.location.reload(true);
        }
    })
};

