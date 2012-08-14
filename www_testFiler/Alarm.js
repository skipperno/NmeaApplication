
var alarmValue = 0; //  alarmState + (alarmConfirmed << 2)
var alarmState = 0;      // 0: NOT ALARM, 1: ALARM SHALLOW, 2: ALARM DEEP
var alarmConfirmed = 0;  // 0: CONFIRMED, 1: NOT CONFIRMED SHALLOW 2: NOT CONFIRMED DEEP
var oldAlarmState = 0;
var oldAlarmConfirmed = 0;

var alarmParentDiv;
var alarmLowDiv;
var alarmHighDiv;


//var hysteresis = 5; // [m]


var bAlarmOdd = false;
var alarmTimer;
var alarmSlidBlinkTimer;
var bAlarmSlidOdd = false;
var sliderBlinkCounter = 0;

var alarmMaxValues = [1600, 5200, 870]; //[meter, feet, fathoms]  or 1600, 5248, 874.88 ???
var alarmMaxValues_L = [100, 328, 55]; //[meter, feet, fathoms]

/* meter                           feet                  fathom      */
var alarmSlidText = [[0,300,600,900,1200,1500],[0,1000,2000,3000,4000,5000], [0,200,400,600,800]];
var alarmSlidTextLow = [[0,20,40,60,80,100],[0,100,200,300], [0,10,20,30,40,50]];

function initAlarm(parentDiv) {
	alarmParentDiv = parentDiv;
	alarmLowDiv = document.createElement("DIV");
	alarmHighDiv = document.createElement("DIV");

	alarmLowDiv.id = "alarmLowDiv";
	// alarmLowDiv.id = "alarmLowDivId" + this.myId;

	alarmHighDiv.id = "alarmHighDiv";
	// alarmLowDiv.id = "alarmHighDivId" + this.myId;
	alarmParentDiv.appendChild(alarmLowDiv);
	alarmParentDiv.appendChild(alarmHighDiv);
	updateAlarmIcons();
	$("#alarmMsgDiv").hide();
	$("#alarmConfirmDiv").hide();
	document.getElementById("alarmStateDiv").innerHTML = "";
	
	oldAlarmConfirmed = 0;  
	oldAlarmState = 0;
	
	$("#alarmConfirmDiv").click(function(e){		
		if (alarmConfirmed != 0) {
			sendToServer(JSON.stringify(jsonAlarmConfirm));
			return preventEv(e);
		}
	});
}


//////////////////////////ALARM SLIDERS ///////////////////////////////////////
function showAlarmSliders() {
	updateAlarm_L();
	updateAlarm_H();
	$('#alarmSlidDiv').show();
}



function updateAlarm_L(){
	$("#alarmSlidDiv_1").empty();
	
	var unitIndex = getDepthUnitStorage();
	var max = alarmMaxValues_L[unitIndex];
	
	var alarmSlidTextPos = new Array();
	
	for (var i = 0; i < alarmSlidTextLow[unitIndex].length; i++) {
		alarmSlidTextPos[i] = parseInt(alarmSlidTextLow[unitIndex][i] * 300 / max); /*slider width=300px*/
	}
	alarmLowSlider = new SliderHorizontalUnlinear(0, "Alarm Shallow",unitText[unitIndex],0, 100, jsonDATA.alarm.L, document
			.getElementById("alarmSlidDiv_1"), alarmSlidTextLow[unitIndex], alarmSlidTextPos, false);
	
	alarmLowSlider.changeUnderText("Alarm Shallow: " + parseInt(jsonDATA.alarm.L*depthConverFactor[unitIndex]) + depthUnit[unitIndex]);
}

function updateAlarm_H(){
	$("#alarmSlidDiv_2").empty();
	
	//var alarmText = new Array();
	var unitIndex = getDepthUnitStorage();
	var max = alarmMaxValues[unitIndex];
	
/*	for (var i = 0; i < 6; i++){
		alarmText[i] = parseInt((max / 5)*i);
	}*/
	
	var alarmSlidTextPos = new Array();
	for (var i = 0; i < alarmSlidText[unitIndex].length; i++) {
		alarmSlidTextPos[i] = parseInt(alarmSlidText[unitIndex][i] * 300 / max); /*slider width=300px*/
	}
	
	alarmHighSlider = new SliderHorizontalUnlinear(1, "Alarm Deep", unitText[unitIndex],0, 1600, jsonDATA.alarm.H, document
			.getElementById("alarmSlidDiv_2"), alarmSlidText[unitIndex], alarmSlidTextPos, false);
	alarmHighSlider.changeUnderText("Alarm Deep: " + parseInt(jsonDATA.alarm.H*depthConverFactor[unitIndex]) + depthUnit[unitIndex]);
}


function updateAlarmSlidersText(){
	if (alarmLowSlider != null && alarmHighSlider != null) {
		var unitIndex = getDepthUnitStorage();
		alarmLowSlider.changeUnderText("Alarm Shallow: " + parseInt(jsonDATA.alarm.L*depthConverFactor[unitIndex]) + depthUnit[unitIndex]);
		alarmHighSlider.changeUnderText("Alarm Deep: " + parseInt(jsonDATA.alarm.H*depthConverFactor[unitIndex]) + depthUnit[unitIndex]);
	}
}
//////////////////////////ALARM SLIDERS END ///////////////////////////////////////

////////////////////////// ALARM SLIDERS BLINK ////////////////////////////////////
var blinkDiv;
function startBlinkSlider(bLowSlider){
	if(bLowSlider)
		blinkDiv = alarmLowSlider.nameDiv;
	else
		blinkDiv = alarmHighSlider.nameDiv;
	
	sliderBlinkCounter = 20;
	blinkAlarmSlider();
}
function blinkAlarmSlider(){
	if (sliderBlinkCounter > 0) {
		alarmSlidBlinkTimer = setTimeout("onSliderBlinkTimeout()", 50);
	} else {
		$(alarmLowSlider.nameDiv).css("color", "#fff");
		$(alarmHighSlider.nameDiv).css("color", "#fff");
	}
}

function stopBlinkAlarmSlider() {
	clearTimeout(alarmSlidBlinkTimer);
	sliderBlinkCounter=0;

	$(alarmLowSlider.nameDiv).css("color", "#fff");
	$(alarmHighSlider.nameDiv).css("color", "#fff");
}

function onSliderBlinkTimeout() {
	sliderBlinkCounter--;
	//var alarmDiv = document.getElementById('alarmMsgDiv');
	
	
	if (bAlarmSlidOdd){
		bAlarmSlidOdd = false;
		$(blinkDiv).css("color", "#f00");//("background", "#f00");
	} else {
		bAlarmSlidOdd = true;
		$(blinkDiv).css("color", "#fff");
	}
	blinkAlarmSlider();
}
//////////////////////////ALARM SLIDERS BLINK END ////////////////////////////////////

function updateAlarmIcons() {
	var alarmLow_Y = parseInt($(alarmParentDiv).height() * jsonDATA.alarm.L
			/ rangeMaxValuesCalculation[jsonDATA.range]);
	alarmLowDiv.setAttribute("style", "top:" + alarmLow_Y + "px");

	var alarmHigh_Y = $(alarmParentDiv).height() * jsonDATA.alarm.H
			/ rangeMaxValuesCalculation[jsonDATA.range];
	if (alarmHigh_Y > $(alarmParentDiv).height()) {
		alarmHigh_Y = $(alarmParentDiv).height();
	}
	
	alarmHighDiv.setAttribute("style", "top:" + (alarmHigh_Y-9) + "px");
	$(alarmHighDiv).show();
	
}

function getAlarmState(){
	if (alarmState == 0 && alarmConfirmed == 0)
		return 0;
	if (alarmState == 0 && alarmConfirmed != 0)
		return 1;
	return 2;
}

function alarmTest(){
	alarmConfirmed = parseInt(alarmValue/4);
	alarmState = alarmValue - alarmConfirmed*4;      // 0: NOT ALARM, 1: ALARM SHALLOW, 2: ALARM DEEP
	
	if(alarmConfirmed > 0 && oldAlarmConfirmed == 0){
		$("#alarmConfirmDiv").show();
	} else if(alarmConfirmed == 0 ) { //}&& oldAlarmConfirmed != 0){
		$("#alarmConfirmDiv").hide();
		stopAlarmTimer();
		$("#alarmMsgDiv").hide();
	}
	
	
	if (alarmState == 0) {
		if(oldAlarmState != 0) { //} && alarmConfirmed == 0){ // state changed
			document.getElementById("alarmStateDiv").innerHTML = "OK";
			$("#alarmStateDiv").css("color", "#000");
		}
	} else {
		if (alarmState == 1 && oldAlarmState != 1) {
			stopAlarmTimer();
			showAlarmMsg();
			document.getElementById("alarmStateDiv").innerHTML = "ALARM SHALLOW";
			$("#alarmStateDiv").css("color", "#FFB121");
		} else if (alarmState == 2 && oldAlarmState != 2) {
			stopAlarmTimer();
			showAlarmMsg();
			document.getElementById("alarmStateDiv").innerHTML = "ALARM DEEP";
			$("#alarmStateDiv").css("color", "#FFB121");
		} else {
			if (jsonAlarmConfirm == 0) {
				stopAlarmTimer();
				$("#alarmMsgDiv").hide();
			}
		}
	}
	
	if (alarmState == 0) {
		if (alarmConfirmed != 0) {
			if (alarmConfirmed == 1 && oldAlarmConfirmed != 1) {
				document.getElementById("alarmStateDiv").innerHTML = "ALARM SHALLOW";
			} else if (alarmConfirmed == 2 && oldAlarmConfirmed != 2) {
				document.getElementById("alarmStateDiv").innerHTML = "ALARM DEEP";
			}	
		}
	}
		
	oldAlarmState = alarmState;
	oldAlarmConfirmed = alarmConfirmed;
	/*
	if (alarmValue == 0) {
		if (buttom < jsonDATA.alarm.L) {
			alarmValue = 1; // new alarm
			showAlarmMsg(true);
		} else if (buttom > jsonDATA.alarm.H) {
			alarmValue = 2; // new alarm
			showAlarmMsg(true);
		}
	} else {
//		if ((buttom > jsonDATA.alarm.L + hysteresis)
//				&& (buttom < jsonDATA.alarm.H - hysteresis)) {
//			alarmValue = 0; // alarm end
//			showAlarmMsg(false);
//		}
	}

	*/
}



function showAlarmMsg() {
	var alarmDiv = document.getElementById('alarmMsgDiv');
	$("#alarmMsgDiv").show();
	
		startAlarmTimer();
		if (alarmState == 1)
			alarmDiv.innerHTML = "ALARM: SHALLOW";
		else if (alarmState == 2)
			alarmDiv.innerHTML = "ALARM: DEEP"; //SHALLOW
		else
			alarmDiv.innerHTML = "ALARM: ERROR 7";
}

function startAlarmTimer(){
	if (alarmValue > 0) {
		alarmTimer = setTimeout("onAlarmTimeout()", 500);
	}
}

function stopAlarmTimer() {
	clearTimeout(alarmTimer);
}

function onAlarmTimeout() {
	var alarmDiv = document.getElementById('alarmMsgDiv');
	
	if (bAlarmOdd){
		bAlarmOdd = false;
		$(alarmDiv).css("color", "#f00");
		$("#alarmMsgDiv").css("backgroundColor", "#fff");
		$("#depthRight").css("backgroundColor", "#fff");
		$("#depthRight").css('color','#FF0000');
	} else {
		bAlarmOdd = true;
		$(alarmDiv).css("color", "#fff");
		$("#alarmMsgDiv").css("backgroundColor", "#f00");
		$("#depthRight").css("backgroundColor", "#f00");
		$("#depthRight").css('color','#fff');
	}
	startAlarmTimer();
}