/**
 * 
 */

var bSigOdd = false;

var selectedPos= 0;

function changeSignalBeamIconPos(newPos){
	var myElement = document.getElementById('boatDiv');  /*7+18 or 27+18 or 35+18 or 55+18*/
	if (newPos == 1){
		myElement.setAttribute("style", "right:25px");
		$('#boatSensDiv').css("background", "#00f");
	} else if (newPos == 2){
		myElement.setAttribute("style", "right:45px");
		$('#boatSensDiv').css("background", "#f00");
	} else if (newPos == 3){
		myElement.setAttribute("style", "right:53px");
		$('#boatSensDiv').css("background", "#0f0");
	} else { //if (newPos == 4){
		myElement.setAttribute("style", "right:73px");
		$('#boatSensDiv').css("background", "#00f");
	}
	selectedPos =newPos;
}
/*
function updateSigBeam(){
	var myElement = document.getElementById('sigDiv');
	if (bSigOdd){
		bSigOdd = false;
		myElement.style.backgroundImage='url(images/sig_a_1.png)';
		//$(myElement).css("background",getSignalColor());
	} else {
		bSigOdd =true;
		myElement.style.backgroundImage='url(images/sig_b_1.png)';
		//$(myElement).css("background","#fff");
	}
}*/

function getSignalColor(){
	if (selectedPos == 1 || selectedPos == 4)
		return "#ffff00";// yellow 
	else if (selectedPos == 2)
		return "#00FF35"; // green
	else 
		return "#ff9700"; // red-orange
}