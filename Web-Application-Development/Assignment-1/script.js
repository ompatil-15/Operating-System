function login() {
    window.location.href = "./login.html";
}

function validate_credentials() {
    var username = document.getElementById("username").value;
    var password = document.getElementById("password").value;
    
    if (username == 'admin' && password == 'onceuponatime') {
        window.location.href = "options.html";
    }
    else{
        alert("Invalid Credentials");
    }

    return false;
} 

function updateCurrentTime() {
    var currentTime = new Date();
    var hours = currentTime.getHours();
    var minutes = currentTime.getMinutes();
    var seconds = currentTime.getSeconds();

    minutes = (minutes < 10) ? "0" + minutes : minutes;
    seconds = (seconds < 10) ? "0" + seconds : seconds;

    var formattedTime = hours + ":" + minutes + ":" + seconds;
    document.getElementById("time").innerText = formattedTime;
}

setInterval(updateCurrentTime, 1000);
updateCurrentTime();

