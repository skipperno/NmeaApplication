/**
 * 
 */

var startSleepTime = 300; // start sleep time is 300ms
var sleepCoef = 0; // sleep time = startSleepTime + sleepCoef*100ms


var timeTextPos_X= [20, 80, 160, 240, 320, 400];


function changeTimeRange(scale){
	sleepCoef = scale;
	var myElement = document.getElementById('timeScale');
	var inner="";
	
	for(i = 0; i < 6; i++) {
		inner +="<div style=\"width:119px; float:right; color:#fff; border-right:1px solid #fff\">" +
		(startSleepTime + sleepCoef*100)*i*120/1000 + "</div>";
	}

	myElement.innerHTML=inner;
	
}