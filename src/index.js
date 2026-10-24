
function changeColour() {
    if(document.getElementById("demo").style.backgroundColor == "red") {
        document.getElementById("demo").style.backgroundColor = "blue";
    }
    else {
        document.getElementById("demo").style.backgroundColor = "red";
    }

}

function main() {
    document.getElementById("demo2").innerHTML = "<h2>Hello World</h2>";
}

function test() {
    document.getElementById("demo2").innerText = "Hello World 2";
    // testing only
    document.write(5 + 6);
}
