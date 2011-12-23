var menuShown = false;
var selectedHorizMenuIndex = -1;
var selectedVerticalMenuIndex = -1;

var selectedIO_source = -1;

var shownScope = false;




function initMenu() {
	initHorisontalSubMenu();
	setMenuShown(false);
}

/** ******************************************** */
/** ******* Button Setup/Exit Menu ****** */
/** ******************************************** */
function onSetupButtonClick() {
	var myElement = document.getElementById('menuOnOffBut');

	if (menuShown) {
		setMenuShown(false);
		//myElement.src = "images/MenuShow.png";
		myElement.style.backgroundImage='url(images/MenuShow3.png)';
	} else {
		setMenuShown(true);
		//onMainMenuClickCallback(-1); //select item 0
		
		myElement.style.backgroundImage='url(images/MenuBack3.png)';
	}
}

function onSetupButtonOver() {
	/*if (!menuShown) {
		var myElement = document.getElementById('menuOnOffBut');
		myElement.style.backgroundImage='url(images/MenuShow_2.png)';
	}*/
}
function onSetupButtonOut() {
	if (!menuShown) {
		var myElement = document.getElementById('menuOnOffBut');
		myElement.style.backgroundImage='url(images/MenuShow3.png)';
		//myElement.src = "images/MenuShow.png";
	}
}

function setMenuShown(show) {
	if (show) {
		//showHorizontalMenu(-1);
		resetVertMenu();
		$(vertMenuSliding).show();
	} else {
		$("#subMenu").animate({top:'60px'},400);
		//showHorizontalMenu(-1);
		resetVertMenu();
		$(vertMenuSliding).hide();
		removeSlider();
	}
	menuShown = show;
}

function removeSlider(){
	removeRangeSlider();
	$('#sliderChoice').empty();
	$('#sliderChoice').hide();
	
	$('#nmeaPanel').hide();
	
	$("#statusDiv").hide();
	
	$("#alarmSlidDiv_1").empty();
	$("#alarmSlidDiv_2").empty();
	$("#alarmSlidDiv").hide();
	removeBigBoat();
	statusShown = false;
	//$("#statusDiv").empty();
}

var statusShown = false;
var showHorisontalMenu;
/** ******************************************** */
/** *******         Vertical Menu Callback              ****** */
/** ******************************************** */
function onMainMenuClickCallback(menuIndex) {
	showHorisontalMenu = true;
	deselectOtherHorizontalMenuItems(-1); //deselect all horisontal items
	removeSlider();
	if (menuIndex == selectedVerticalMenuIndex) { // the same item, remove menu
		if (menuIndex == PICT_SPEED) { //TRANSDUCER) {
			onBoatIconPush(); // remove boat icon
		}
		setMenuShown(false);
		return;
	}
	
	if (menuIndex != -1) {
		$("#subMenu").animate({top:'60px'},200);
	} else
		menuIndex = 0;
	
	if(menuIndex == STATUS){
		if(statusShown){
			$("#statusDiv").hide();
			statusShown = false;
		} else {
			$("#statusDiv").show();
			statusShown = true;
		}
		showHorisontalMenu = false;
		//return;
	} else if (menuIndex == TRANSDUCER) { 
		showHorisontalMenu = false;
		onBoatIconPush();
	} else if (menuIndex == PICT_SPEED) { 
		showHorisontalMenu = false;
		showTimeScaleCheckBox();
	} else if (menuIndex == MARK) {
		showHorisontalMenu = false;
		echoCanvas1.paintMark();
	} else if (menuIndex == ALARMS) {
		showHorisontalMenu = false;
		showAlarmSliders();
	}
		
	
	selectVerticalMenu(menuIndex);	
	selectedVerticalMenuIndex = menuIndex;
	
	/*$("#menuBar").css('top','240px');
	$("#menuBar").css('left','470px');
	$("#menuBar").animate({left:'0px'},300);
	$("#menuBar").animate({top:'360px'},400);*/
	
	/*$("#menuBar").css('left','470px');
	$("#menuBar").animate({left:'0px'},300);*/
	if(showHorisontalMenu) {
		showHorizontalMenu(menuIndex);
		
		$("#subMenu").css('top','60px');
		$("#subMenu").animate({top:'0px'},400);
	}
}

function onPictureSpeedButtonPush() {
	if(boatShown){
		removeTimeSlider();
	} else {
		showTimeSlider();
	}
}

function onBoatIconPush(){
	if(boatShown){
		//verMenuArray[TRANSDUCER].selected = false;
		removeBigBoat();
		/*$('#sliderChoice').hide();
		$('#sliderChoice').empty();*/
	} else {
		//verMenuArray[TRANSDUCER].selected = true;
		showBigBoat();
		//showPosition();
		//onMainMenuClickCallback(TRANSDUCER);
	}
		
}

function onHorisontalMenuCallback(menuIndex, pushed) {
	if (pushed) {
		if (selectedHorizMenuIndex > -1) { // other button was pushed 
			
		}
		selectedHorizMenuIndex = menuIndex;
	} else {
		selectedHorizMenuIndex = -1;
		$('#sliderChoice').hide();
	}
	
	switch(menuIndex){
	/*	case AL_L:
		if (pushed)
			showAlarm_L();  
		else
			$('#sliderChoice').empty();
		break;
	case AL_H:
		if (pushed)
			showAlarm_H(); 
		else
			$('#sliderChoice').empty();
		break;
	case 2: //MARK
		if (pushed)
			showPosition();
		else
			$('#sliderChoice').empty();
		break;
	case POSITION: //POSITION
		if (pushed)
			showPosition();
		else
			$('#sliderChoice').empty();
		break;*/
	/*case 4: //DRAUGHT
		if (pushed)
			// 
		else
			$('#sliderChoice').empty();
		break;
		
	case MODE: //MODE

		break;*/
	case GAIN: // GAIN
		if (pushed)
			showGain();
		else
			$('#sliderChoice').empty();
		break;
		
	case TVG: // TVG
		if (pushed)
			showTVG();
		else
			$('#sliderChoice').empty();
		break;
	case PWR: // PWR
		if (pushed)
			showPOW();
		else
			$('#sliderChoice').empty();
		break;
		
	case COM1:
		selectedIO_source = 2; // COM2
		nmeaIO_PanelPopulate();
		
		if (pushed) {
			$("#nmeaPanel").show();
		} else {
			$("#nmeaPanel").hide();
		}
		break;
	case COM2: //COM2
		selectedIO_source = 3; // COM3
		nmeaIO_PanelPopulate();
		
		if (pushed) {
			$("#nmeaPanel").show();
		} else {
			$("#nmeaPanel").hide();
		}
		break;
		
	case LAN: //LAN // !!! Now is Green-Blue
		selectedIO_source = 4; // LAN
		nmeaIO_PanelPopulate();
		
		if (pushed) {
			changeToGreen();
		} else {}
		break;
	case CAN: //CAN //!!! Now is Scope
		selectedIO_source = 5; // CAN
		if (pushed) {
			changeHorMenuButtonValue(menuIndex, "On");
			changeToScopeScreen();
		} else {
			changeHorMenuButtonValue(menuIndex, "Off");
			changeToEchoScreen();
		}
		break;
	case COLOR:
		showColor();
		break;
	case TRANSCEIVER:
		if (pushed) {
			$("#transceiverDiv").show();
		} else {
			$("#transceiverDiv").hide();
			}
		break;
		
	default:
		deselectOtherHorizontalMenuItems(-1); //deselect all horizontal items
		alert("NOT IMPELMENTED");
		break;
	}
}

function nmeaIO_PanelPopulate(){
	$('#nmeaOutputs').populate(jsonIO.set[selectedIO_source - 1]);
	$('#diplayForm').populate(jsonIO.set[selectedIO_source - 1].disRadio);
	$('#comBaud').populate(jsonIO.set[selectedIO_source - 1].baudR);
}



function onSliderMoved(sliderIndex, pos) {

	if (sliderIndex == 0) { 
		jsonDATA.alarm.L = pos;
		updateAlarmIcons();
		sendToServer(JSON.stringify(jsonDATA));
	} else  if (sliderIndex == 1) {
		jsonDATA.alarm.H = pos;
		updateAlarmIcons();
		sendToServer(JSON.stringify(jsonDATA));
	} else  if (sliderIndex == 3) { // transducer position
		onBigBoatClick( pos + 1);
		
		if(jsonTransceiver.jsonTransceiverCH1.position == pos)
			jsonTransceiver.activeCh = 0;
		else if(jsonTransceiver.jsonTransceiverCH2.position == pos)
			jsonTransceiver.activeCh = 1;
		
		updateTransceiverInfo();
		
		//"fwd", "port", "stb", "aft"
		if(pos == 3) {
			menuArray[3].changeValueText("fwd");
		} else if(pos == 2) 
			menuArray[3].changeValueText("port");
		else if(pos == 1) 
			menuArray[3].changeValueText("stb");
		else if(pos == 0) 
			menuArray[3].changeValueText("aft");
		//sendToServer(JSON.stringify(jsonDATA));
	}  else if (sliderIndex == 6){
		jsonDATA.signal.GAIN=pos;
		sendToServer(JSON.stringify(jsonDATA));
	} else if (sliderIndex == 7){
		jsonDATA.signal.TVG=pos;
		sendToServer(JSON.stringify(jsonDATA));
	} else if (sliderIndex == 8){
		jsonDATA.signal.POW=pos;
		sendToServer(JSON.stringify(jsonDATA));
	} else if (sliderIndex == 100){  // RANGE
		changeRange(pos); 
		jsonDATA.range = pos;
		sendToServer(JSON.stringify(jsonDATA));
	} else if (sliderIndex == 101) { // TIME   
		changeTimeRange(pos); 
	} else if (sliderIndex == 51) { // BRIGHTNES
		onBrightnes(pos);  // defined in Light.js
	} else if (sliderIndex == 52) { // LIGHT PRESETS
		onLightPresets(pos); 
	} else if (sliderIndex == 53) { // DAY/NIGHT
		onDayNight(pos); 
	} else if(sliderIndex == 202) { 		// Position changed
		selectedTranscChannel.position = pos;
	} else if(sliderIndex == 203) { // Freq. 1 changed
		selectedTranscChannel.freq1 = pos;
		sliderFreq1.changeUnderText("Frequency: " + pos*10 + "kHz");
		updateTransceiverInfo();
	} else if(sliderIndex == 204) { // Freq. 2 changed
		selectedTranscChannel.freq2 = pos;
		sliderFreq2.changeUnderText("Frequency: " + pos*10 + "kHz");
	} else  if (sliderIndex == 701) { // Color
		changeColor(pos);
	}

}

function showAlarmSliders() {
	showAlarm_L();
	showAlarm_H();
	$('#alarmSlidDiv').show();
}

function showAlarm_L(){
	//$("#alarmSlidDiv_1").empty();
	//$('#sliderChoice').empty();

	var alarmText = [ "0m", "320m", "640m", "960m", "1280m", "1600m" ];
	var mySlider = new SliderHorizontal(0, "Alarm Shallow",0, 1600, jsonDATA.alarm.L, document
			.getElementById("alarmSlidDiv_1"), alarmText, false);
	$('#sliderChoice').show();
	//$('#sliderChoice').show();
}

function showAlarm_H(){
	//$('#alarmSlidDiv_2').empty();

	var alarmText = [ "0m", "320m", "640m", "960m", "1280m", "1600m" ];
	var mySlider = new SliderHorizontal(1, "Alarm Deep",0, 1600, jsonDATA.alarm.H, document
			.getElementById("alarmSlidDiv_2"), alarmText, false);

	//$('#sliderChoice').show();
}

function showPosition(){
	$('#sliderChoice').empty();
	var choiseTextArray = ["aft", "stb","port", "fwd"];
	var activeChannel;
	
	if(jsonTransceiver.activeCh == 0)
		activeChannel = jsonTransceiver.jsonTransceiverCH1;
	else if(jsonTransceiver.activeCh == 1)
		activeChannel = jsonTransceiver.jsonTransceiverCH2;
	
	
	var testChoice = new ChoiceBoxHoriz2(3, "Position", activeChannel.position, document.getElementById("sliderChoice"), 4, choiseTextArray, "Checkbox.png", "CheckboxFull.png", 48,48,400, 90);

	$('#sliderChoice').show();
}




function showColor(){
	$('#sliderChoice').empty();
	var choiseTextArray = ["Normal", "Green","Blue", "Wrong"];
	var activeChannel;
	
	var testChoice = new ChoiceBoxHoriz2(701, "Color", 0, document.getElementById("sliderChoice"), 4, choiseTextArray, "Checkbox.png", "CheckboxFull.png", 48,48,400, 90);

	$('#sliderChoice').show();
}


function showGain() {
	$('#sliderChoice').empty();

	var gainText = [ "0%", "20%", "40%", "60%", "80%", "100%" ];
	var mySlider = new SliderHorizontal(6, "GAIN",0, 100, jsonDATA.signal.GAIN, document
			.getElementById("sliderChoice"), gainText, false);

	$('#sliderChoice').show();
}

function showTVG(){
	$('#sliderChoice').empty();

	var tvgText = [ "0%", "20%", "40%", "60%", "80%", "100%" ];
	var mySlider = new SliderHorizontal(7, "TVG",0, 100, jsonDATA.signal.TVG, document
			.getElementById("sliderChoice"), tvgText, false);

	$('#sliderChoice').show();
}

function showPOW(){
	$('#sliderChoice').empty();

	var tvgText = [ "0%", "20%", "40%", "60%", "80%", "100%" ];
	var mySlider = new SliderHorizontal(8, "POWER",0, 100, jsonDATA.signal.TVG, document
			.getElementById("sliderChoice"), tvgText, false);

	$('#sliderChoice').show();
}

function showFREQ(){
	$('#sliderChoice').empty();

	var tvgText = [ "0%", "20%", "40%", "60%", "80%", "100%" ];
	var mySlider = new SliderHorizontal(9, "FREQ",0, 100, jsonDATA.signal.TVG, document
			.getElementById("sliderChoice"), tvgText, false);

	$('#sliderChoice').show();
}
/*
function showBaudRate(){
	$('#sliderChoice').empty();
	var choiseTextArray = [ "9600", "2400", "19200", "56000", "115200", "256000"];
	var testChoice = new ChoiceBoxHoriz(13, "Baud rate", 2, document.getElementById("sliderChoice"), 6, choiseTextArray);

	$('#sliderChoice').show();
}

function showParity(){
	$('#sliderChoice').empty();
	var choiseTextArray = [ "odd", "even"];
	var testChoice = new ChoiceBoxHoriz(14, "Baud rate", 1, document.getElementById("sliderChoice"), 2, choiseTextArray);

	$('#sliderChoice').show();
}*/




