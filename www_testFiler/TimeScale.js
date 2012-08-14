/**
 * 
 */

var sleepTimeIndex = -1;

var timeText		=["60min", "15min", "10min", "5min", "2min", "1min"];
var paintSleepTime	=[6664, 1666, 1111, 555, 222, 111]; //[ms]
var timeLinesCount	=[6, 3, 5, 5, 4, 6];

var timeCounter = 0;


function getSleepTimeIndex() {
	if (sleepTimeIndex == -1)
		sleepTimeIndex = getTimeScaleStorage();
	return sleepTimeIndex;
}


function showTimeScaleCheckBox(){
	$('#sliderChoice').empty();
	//var choiseTextArray = ["15min", "10min", "5min", "2min", "1min"];//["16:40","09:00", "04:30","01:48", "00:54"];
	var activeChannel;
	
	var testChoice = new ChoiceBoxHoriz2(101, "Total time", getTimeScaleStorage(), document.getElementById("sliderChoice"), 6, timeText, "ComBox_A.png", "ComBox_B.png", 60,55,400, 70);

	$('#sliderChoice').show();
}



function updateScreenSpeedTime() {
	
}


function changeTimeRange(scale) {
	var oldTime = timeText[getSleepTimeIndex()];
	sleepTimeIndex = scale;
	var myElement = document.getElementById('timeScale');
	var inner="";

	//inner +="<div style=\"width:7px; position:absolute; right:" + timeTextPos_X[0] + "px;\"><img src=\"images/timeScalBack.png\" height=\"18\" width=\"7\" /></div>";
	
	inner +="<div style=\"width:103px; position:absolute; left:5px; text-align:left; color:#fff;\">" + timeText[sleepTimeIndex] + "</div>";
	
	var linePixStep = CANVAS_WIDTH / timeLinesCount[scale];
	
	for(i = 0; i < timeLinesCount[scale]-1; i++) {
		inner +="<div style=\"width:7px; position:absolute; right:" + linePixStep*(i+1) + "px;\"><img src=\"images/timeScalBack.png\" width=\"7\" /></div>";
	}

	myElement.innerHTML=inner;
	// update also value i table on the top of screen
	myElement = document.getElementById('scrSpeed');
	myElement.innerHTML = timeText[sleepTimeIndex];
		
	setTimeScaleStorage(scale);

	if (echoCanvas1 != null)
	paintMsgLine3px(echoCanvas1.canvasDoubleBuffer2Dcontext, CANVAS_WIDTH - 1, CANVAS_HEIGHT, "Time scale", oldTime, timeText[sleepTimeIndex]);
}