// JavaScript source code
//listen to call validation function using the DOM
document.getElementById("btnDogSubmit").addEventListener("click", validateDogForm);

//function to perform client-side form validation and alerts the user of missing input
function validateDogForm() {
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
        //send info to database
    }

}

/***************************************************************************************
*   function to delete an a dog, sends the dog's id to the server as a delete request
*  --SOURCE--
*    Title: deleteperson.js
*    Authors: Justin Wolford, Samarendra Hedao
*    Initial Publish Date: 10/25/2017
*    Code version: <code version>
*    Availability: https://github.com/knightsamar/CS340-Sample-Web-App/tree/master/public
***************************************************************************************/
function deleteDog(id) {
    $.ajax({
        url: '/dogs/' + id,
        type: 'DELETE',
        success: function (result) {
            window.location.reload(true);
        }
    })
};