let number = 0;
document.getElementById("number").innerHTML = number;
function increaseNumber() {
    number++;
}
function decreaseNumber() { 
    if(number < 0) {
        number = 0;
    } else if (number > 0) {
        number--;        
    }
}
function displayNumber() {
    document.getElementById("number").innerHTML = number;
}