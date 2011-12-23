/**
 * 
 */

var sleepTimeIndex = 0;
var paintSleepTime=[2000, 1000, 500, 200, 100]; //[ms]
var timeText=[200, 100, 50, 20, 10]; //[sec]
//100px = 200sec, 100sec, 50 sec, 20 sec, 10 sec

var timeTextPos_X= [100, 200, 300, 400, 500]; // !!! distance from right edge


function showTimeScaleCheckBox(){
	$('#sliderChoice').empty();
	var choiseTextArray = ["200 sec <br \>pr route","100 sec <br \>pr route", "50 sec <br \>pr route","20 sec <br \>pr route", "10 sec <br \>pr route"];
	var activeChannel;
	
	var testChoice = new ChoiceBoxHoriz2(101, "Picture Speed", getTimeScaleStorage(), document.getElementById("sliderChoice"), 5, choiseTextArray, "ComBox_A.png", "ComBox_B.png", 78,55,400, 110);
	//var testChoice = new ChoiceBoxHoriz2(101, "Picture Speed", 0, document.getElementById("sliderChoice"), 5, choiseTextArray, "Checkbox.png", "CheckboxFull.png", 48,48,400, 90);

	$('#sliderChoice').show();
}

var timeCounter = 0;

function updateScreenSpeedTime() {

}


function changeTimeRange(scale) {
	sleepTimeIndex = scale;
	var myElement = document.getElementById('timeScale');
	var inner="";

	inner +="<div style=\"width:7px; position:absolute; right:" + timeTextPos_X[0] + "px;\"><img src=\"images/timeScalBack.png\" height=\"18\" width=\"7\" /></div>";
	
	inner +="<div style=\"width:103px; margin-right:8px; position:absolute; right:" + timeTextPos_X[0] + "px; color:#fff;\">" + timeText[sleepTimeIndex] + " sec</div>";
	
	for(i = 1; i < 5; i++) {
		inner +="<div style=\"width:7px; position:absolute; right:" + timeTextPos_X[0]*(i+1) + "px;\"><img src=\"images/timeScalBack.png\" width=\"7\" /></div>";
	//	inner +="<div style=\"width:103px; margin-right:8px; position:absolute; right:" + timeTextPos_X[0]*(i+1) + "px; color:#fff;\">" + timeText[sleepTimeIndex]*(i+1) + " sec</div>";
	}

	myElement.innerHTML=inner;
	setTimeScaleStorage(scale);
}