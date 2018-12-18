// JavaScript source code
/***************************************************************************************
*   function to search the dogs table, sends the searched for name, birthdate, breed, 
*   sex, food, and adopter to the server
*  --SOURCE--
*    Title: searchpeople.js
*    Authors: Samarendra Hedao
*    Initial Publish Date: 06/10/2018
*    Availability: https://github.com/knightsamar/CS340-Sample-Web-App/tree/master/public
***************************************************************************************/
function searchDogs() {
    var name = document.getElementById('name').value;
    var birthdate = document.getElementById('birthdate').value;
    var breed = document.getElementById('breed').value;
    var sex = document.getElementById('sex').value;
    var foodID = document.getElementById('food').value;
    var adoptedID = document.getElementById('adopter').value;

    if (name == "") {
        name = "none";
    }

    if (birthdate == "") {
        birthdate = "none";
    }

    if (breed == "") {
        breed = "none";
    }

    window.location = '/dogsearch/' + name + '/' + birthdate + '/' + breed + '/' + foodID + '/' + sex + '/' + adoptedID;
   
}