
function showScreenHardware(){
	screenShown = true;
	$("#ScreenHardware").show();
}

function removeScreenHardware(){
	screenShown = false;
	$("#ScreenHardware").hide();
}

var distArrayText=["1m","2m","3m","5m"]; // !!! the same in "FontSize.js"
var screenSizeText=["8''","10''"];

function initScreenHardware(){
	var myElem = document.getElementById("ScreenHardware"); 
	
	myElem.innerHTML =
	"<div class='mainTableHeader'>HARDWARE SETUP</div>" +
	"<div id = 'distance' class='screenGroupe'></div>" + 
	"<div id = 'screenSize' class='screenGroupe'></div>" + 
	"<div class='timeConf'><div class='timeCells'><div class='timeCell' id='timeH1'>0</div> <div class='timeCell' id='timeH2'>0</div></div><div class='timeButtons'><div id='timeHup'></div><div id='timeHdown'></div></div>" + 
    "</div>";
	
	var viewDistCB= new ChoiceBoxHoriz2(601, "Viewing distance", getViewingDistanceStorage(), document.getElementById("distance"), 4, distArrayText, "ComBox_A2.png", "ComBox_B2.png", 36,26,180, 50);//144, 50);
	var scrSizeCB = new ChoiceBoxHoriz2(602, "Screen size", getScreenSizeStorage(), document.getElementById("screenSize"), 2, screenSizeText, "ComBox_A2.png", "ComBox_B2.png", 36,26,90, 50);//144, 50);
	
	
	$(myElem).click(function(e){
		return preventEv(e);
	});
	
	new Button(65, document.getElementById("timeHup"), "", "", "goUp.png", "goUp.png", "goUp.png", 30, 25, onHourChanged);
	new Button(66, document.getElementById("timeHdown"), "", "", "goDown.png", "goDown.png", "goDown.png", 30, 25, onHourChanged);
}

function onViewingDistanceEvent(evIndex){
	setViewingDistanceStorage(evIndex);
	initDepthText(); // recalculate
}

function onScreenSizeEvent(evIndex){
	setScreenSizeStorage(evIndex);
	initDepthText(); // recalculate
}
var nHour = 0;

function onHourChanged (evSourceId){
	if(evSourceId == 65) {
		nHour ++;
	} else {
		nHour --;
	}
	if (nHour > 23)
		nHour = 0;
	else if (nHour < 0)
		nHour = 23;
	
	var h1 = parseInt(nHour / 10);
	var h2 = nHour - h1*10;
	document.getElementById("timeH1").innerHTML = h1;
	document.getElementById("timeH2").innerHTML = h2;
}
