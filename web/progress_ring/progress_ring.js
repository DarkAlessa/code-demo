var label = document.querySelector('.label');
var ring = document.querySelector(".ring_outer");
var ring_blur = document.querySelector(".ring_blur");
var radius = ring.r.baseVal.value;
var circumference = radius * 2 * Math.PI;

ring.style.strokeDasharray = `${circumference} ${circumference}`;
ring.style.strokeDashoffset = `${circumference}`;
ring_blur.style.strokeDasharray = `${circumference} ${circumference}`;
ring_blur.style.strokeDashoffset = `${circumference}`;
label.textContent = "0%";

/*
function setProgress(percent) {
	const offset = circumference - percent / 100 * circumference;
	ring.style.strokeDashoffset = offset;
	ring_blur.style.strokeDashoffset = offset;
	label.textContent = percent + "%";
}
*/

var percent = 0;
setInterval(function() {
	const offset = circumference - percent / 100 * circumference;
	ring.style.strokeDashoffset = offset;
	ring_blur.style.strokeDashoffset = offset;
	label.textContent = percent + "%";
	percent++;
	if(percent == 100) {
		percent = 0;
	}
}, 100);
