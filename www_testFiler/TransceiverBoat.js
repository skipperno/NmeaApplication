/**
 * 
 */

var bSigOdd = false;
var botImgType = 2;
var selectedPos= 0;

var boatShown = false;


function showBigBoat(){
	$("#boatBigDiv").show();
	boatShown = true;
}

function removeBigBoat(){
	$("#boatBigDiv").hide();
	boatShown = false;
}

function onBigBoatClick(iconIndex){
	var myElement = document.getElementById('boatDiv');  /*7+18 or 27+18 or 35+18 or 55+18*/
	if(botImgType == 1){
		if (newPos == 1){
			myElement.style.backgroundImage='url(images/boat_40_A.png)';
		} else if (newPos == 2){
			myElement.style.backgroundImage='url(images/boat_40_S.png)';
		} else if (newPos == 3){
			myElement.style.backgroundImage='url(images/boat_40_P.png)';
		} else { //if (newPos == 4){
			myElement.style.backgroundImage='url(images/boat_40_F.png)';
		}
	} else {
		if (newPos == 1){
			myElement.style.backgroundImage='url(images/boat_40_A2.png)';
		} else if (newPos == 2){
			myElement.style.backgroundImage='url(images/boat_40_S2.png)';
		} else if (newPos == 3){
			myElement.style.backgroundImage='url(images/boat_40_P2.png)';
		} else { //if (newPos == 4){
			myElement.style.backgroundImage='url(images/boat_40_F2.png)';
		}
	}
	selectedPos =newPos;
}



function getSignalColor(){
	if (selectedPos == 1 || selectedPos == 4)
		return "#ffff00";// yellow 
	else if (selectedPos == 2)
		return "#00FF35"; // green
	else 
		return "#ff9700"; // red-orange
}