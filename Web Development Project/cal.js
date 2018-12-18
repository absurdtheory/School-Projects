document.getElementById("subButton").addEventListener("click", validateForm);

function displaySubmit() {
    document.getElementById("request").innerHTML = "Your appointment request has been submitted!";
}


function validateForm() {
    var x = document.forms["appReq"]["fname"].value;
    var y = document.forms["appReq"]["email"].value;
    var z = document.forms["appReq"]["phone"].value;
    var d = document.forms["appReq"]["date"].value;
    var t = document.forms["appReq"]["time"].value;
    if (x == "") {
        alert("Name must be filled out");
        return false;
    }
    else if (y == "") {
        alert("Email must be filled out");
        return false;
    }
    else if (z == "") {
        alert("Phone must be filled out");
        return false;
    }
    else if (d == "") {
        alert("Date must be filled out");
        return false;
    }
    else if (t == "") {
        alert("Time must be filled out");
        return false;
    }
    else {
        displaySubmit();
    }
    
}