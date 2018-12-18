document.getElementById("subButton").addEventListener("click", validateForm);

function displaySubmit() {
    document.getElementById("request").innerHTML = "Submitted!";
}

function validateForm() {
    var x = document.forms["contactUs"]["fullName"].value;
    var y = document.forms["contactUs"]["email"].value;
    var z = document.forms["contactUs"]["phone"].value;
    var t = document.forms["contactUs"]["message"].value;
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
    else if (t == "") {
        alert("Message must be filled out");
        return false;
    }
    else {
        displaySubmit();
    }

}