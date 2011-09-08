var alarmParentDiv;
var alarmLowDiv;
var alarmHighDiv;

var alarmValue = 0; // 0: not Alarm, 1 alarm low, 2 alarm high
var hysteresis = 5; // [m]


var bAlarmOdd = false;
var alarmTimer;

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
}

function updateAlarmIcons() {
	var alarmLow_Y = parseInt($(alarmParentDiv).height() * jsonDATA.alarm.L
			/ rangeMaxValues[jsonDATA.range]);
	alarmLowDiv.setAttribute("style", "top:" + alarmLow_Y + "px");

	var alarmHigh_Y = $(alarmParentDiv).height() * jsonDATA.alarm.H
			/ rangeMaxValues[jsonDATA.range];
	if (alarmHigh_Y > $(alarmParentDiv).height()) {
		$(alarmHighDiv).hide();
	} else {
		alarmHighDiv.setAttribute("style", "top:" + (alarmHigh_Y-12) + "px");
		$(alarmHighDiv).show();
	}
}



function alarmTest(buttom) {
	//var alarmNewValue = 0;

	if (alarmValue == 0) {
		if (buttom < jsonDATA.alarm.L) {
			alarmValue = 1; // new alarm
			showAlarmMsg(true);
		} else if (buttom > jsonDATA.alarm.H) {
			alarmValue = 2; // new alarm
			showAlarmMsg(true);
		}
	} else {
		if ((buttom > jsonDATA.alarm.L + hysteresis)
				&& (buttom < jsonDATA.alarm.H - hysteresis)) {
			alarmValue = 0; // alarm end
			showAlarmMsg(false);
		}
	}

	//alarmValue = alarmNewValue;
}

function showAlarmMsg(show) {
	var alarmDiv = document.getElementById('alarmMsgDiv');
	
	if (show) {
		startAlarmTimer();
		if (alarmValue == 1)
			alarmDiv.innerHTML = "ALARM: SHALLOW";
		else if (alarmValue == 2)
			alarmDiv.innerHTML = "ALARM: DEEP"; //SHALLOW
		else
			alarmDiv.innerHTML = "ALARM: ERROR 7";
		$(alarmDiv).show();
	} else {
		stopAlarmTimer();
		$(alarmDiv).hide();
	}
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
	} else {
		bAlarmOdd = true;
		$(alarmDiv).css("color", "#f80");
	}
	startAlarmTimer();
}