//listen to call validation function using the DOM
document.getElementById("btnOrderSubmit").addEventListener("click", validateOrderForm);

//function to validate the form has been filled out properly
function validateOrderForm() {
    var y = document.forms["addfoodorderform"]["quantity"].value;

    if (y == "") {
        alert("Enter Quantity Ordered");
        return false;
    }
    else if (y < 0) {
        alert("Quantity must be greater than 0");
        return false;
    }

}


/***************************************************************************************
*   function to delete a food order, sends the food's id, employee's id, and the datetime
*   to the server as a delete request
*  --SOURCE--
*    Title: deleteperson.js
*    Authors: Justin Wolford, Samarendra Hedao
*    Initial Publish Date: 10/25/2017
*    Availability: https://github.com/knightsamar/CS340-Sample-Web-App/tree/master/public
***************************************************************************************/
function deleteOrder(fid, eid, dateOrdered) {
    $.ajax({
        url: '/orders/FoodSupplyID/' + fid + '/EmployeeID/' + eid + '/DateOrdered/' + dateOrdered,
        type: 'DELETE',
        success: function (result) {
            if (result.responseText != undefined) {
                alert(result.responseText)
            }
            else {
                window.location.reload(true)
            }
        }
    })
};