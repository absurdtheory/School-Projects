/***************************************************************************************
*   function to delete an work relationship, sends the employees's id to and the 
*   dog's id to the server as a delete request
*  --SOURCE--
*    Title: deleteperson.js
*    Authors: Justin Wolford, Samarendra Hedao
*    Initial Publish Date: 10/25/2017
*    Code version: <code version>
*    Availability: https://github.com/knightsamar/CS340-Sample-Web-App/tree/master/public
***************************************************************************************/
function deleteWork(eid, did) {
    $.ajax({
        url: '/works/EmployeeID/' + eid + '/DogID/' + did,
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
