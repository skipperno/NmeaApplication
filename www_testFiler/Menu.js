var menuShown = false;
var selectedHorizMenuIndex = -1;
var selectedVerticalMenuIndex = -1;

var selectedIO_source = -1;

var shownScope = false;

var alarmLowSlider;
var alarmHighSlider;


function initMenu() {
	initHorisontalSubMenu();
	setMenuShown(false);
}

function onMainCenterClick() {
	
	//if (menuShown) {
		setMenuShown(false);
		removeSlider();
	//}
}
/** ******************************************** */
/** ******* Button Setup/Exit Menu ****** */
/** ******************************************** */
function onSetupButtonClick() {
	var myElement = document.getElementById('menuOnOffBut');

	if (menuShown) {
		setMenuShown(false);
		$(myElement).show();
		//myElement.src = "images/MenuShow.png";
		//myElement.style.backgroundImage='url(images/VerMenuItemBackround.png)';
	} else {
		$(myElement).hide();
		setMenuShown(true);
		//onMainMenuClickCallback(-1); //select item 0
		
		//myElement.style.backgroundImage='url(images/MenuBack3.png)';
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
		myElement.style.backgroundImage='url(images/VerMenuItemBackround.png)';
		//myElement.src = "images/MenuShow.png";
	}
}

function setMenuShown(show) {
	if (show) {
		$("#menuOnOffBut").hide();
		//showHorizontalMenu(-1);
		resetVertMenu();
		$(vertMenuSliding).show();
	} else {
		$("#subMenu").animate({top:'60px'},400);
		//showHorizontalMenu(-1);
		resetVertMenu();
		$(vertMenuSliding).hide();
		removeSlider();
		$("#menuOnOffBut").show();
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
	$('#setupPanel').hide();
	$('#transceiverDiv').hide();
	removeScreenHardware();
	removeScreenSetup();
	removeComSetup();
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
	} else if (menuIndex == SETUP) {
		showHorisontalMenu = false;
		showScreenSetup(); //updateSetupScreenValues();?
		//showSetup();
	} /*else if (menuIndex == DIAGN) {
		showHorisontalMenu = false;
		showAlarmSliders();
	} */
		
	
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
		selectedIO_source = 0; // COM2
		
		if (pushed) {
			showComSetup();
			initScreenCom();
			document.getElementById("screanComHeaderText").innerHTML = "SCREEN COM 1 SETUP";
			document.getElementById("nmeaOutInText").innerHTML = "Messages NMEA 1";
			sendToServer(JSON.stringify(jsonIO.set[selectedIO_source]));
		} else {
			removeComSetup();
		}
		break;
	case COM2: //COM2
		selectedIO_source = 1; // COM3
		
		if (pushed) {
			showComSetup();
			initScreenCom();
			document.getElementById("screanComHeaderText").innerHTML = "SCREEN COM 2 SETUP";
			document.getElementById("nmeaOutInText").innerHTML = "Messages NMEA 2";
			sendToServer(JSON.stringify(jsonIO.set[selectedIO_source]));
		} else {
			removeComSetup();
		}
		break;
		
	case LAN: //LAN // !!! Now is Green-Blue
		selectedIO_source = 2; // LAN
		nmeaIO_PanelPopulate();
		initScreenCom();
		break;
	case CAN: //CAN //!!! Now is Scope
		selectedIO_source = 3; // CAN
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
			showChannel(0);
		} else {
			$("#transceiverDiv").hide();
			}
		break;
	case HARDWARE:
		showScreenHardware();
		break;

	case SIMULATOR:
	if (jsonSimulator.sim == 0) {
		changeHorMenuButtonValue(SIMULATOR, "ON");
		jsonSimulator.sim = 1;
	} else {
		changeHorMenuButtonValue(SIMULATOR, "OFF");
		jsonSimulator.sim = 0;
	}
	sendToServer(JSON.stringify(jsonSimulator));
	break;
	
	case SCOPE: 
		if (pushed) {
			changeHorMenuButtonValue(menuIndex, "ON");
			changeToScopeScreen();
		} else {
			changeHorMenuButtonValue(menuIndex, "OFF");
			changeToEchoScreen();
		}
		break;
		
	default:
		deselectOtherHorizontalMenuItems(-1); //deselect all horizontal items
		alert("NOT IMPELMENTED");
		break;
	}
}

function nmeaIO_PanelPopulate(){
	initScreenCom();
	//$('#nmeaOutputs').populate(jsonIO.set[selectedIO_source]);
	//$('#diplayForm').populate(jsonIO.set[selectedIO_source].disRadio);
	//$('#comBaud').populate(jsonIO.set[selectedIO_source].baudR);
}



function onSliderMoved(sliderIndex, pos) {

	if (sliderIndex == 0) { 
		jsonDATA.alarm.L = pos;
		if (jsonDATA.alarm.L > jsonDATA.alarm.H && alarmHighSlider!= null){
			startBlinkSlider(false);
			alarmHighSlider.setHandlButtValue(pos, true);
			jsonDATA.alarm.H = pos;
		}
		updateAlarmIcons();
		updateAlarmSlidersText();
		sendToServer(JSON.stringify(jsonDATA));
	} else  if (sliderIndex == 1) {
		jsonDATA.alarm.H = pos;
		if (jsonDATA.alarm.L > jsonDATA.alarm.H && alarmLowSlider!=null){
			startBlinkSlider(true);
			alarmLowSlider.setHandlButtValue(pos, true);
			jsonDATA.alarm.L = pos;
		}
		updateAlarmIcons();
		updateAlarmSlidersText();
		sendToServer(JSON.stringify(jsonDATA));
	} else if (sliderIndex == 6){
		jsonDATA.signal.GAIN=pos;
		sendToServer(JSON.stringify(jsonDATA));
	} else if (sliderIndex == 7){
		jsonDATA.signal.TVG=pos;
		sendToServer(JSON.stringify(jsonDATA));
	} else if (sliderIndex == 8){
		jsonDATA.signal.POW=pos;
		sendToServer(JSON.stringify(jsonDATA));
	} else if (sliderIndex == 100){  // RANGE
		// DONOT change range. It will be done when next sensor message received
		// changeRange(pos); 
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
		onTransPosChanged(pos);
	} else if(sliderIndex == 203) { // Freq. 1 changed
		onFreqSliderMoved(false, pos);
	} else if(sliderIndex == 204) { // Freq. 2 changed
		onFreqSliderMoved(true, pos);
	} else  if (sliderIndex == 501) { // Setup  screen(Depth Type)
		onDepthTypeCheckboxEvent(pos);
	} else  if (sliderIndex == 502) { // Setup  screen(Depth Unit)
		onDepthUnitCheckboxEvent(pos);
	} else  if (sliderIndex == 503) { // Setup  screen(Font Size)
		onDepthFontEvent(pos);
	} else  if (sliderIndex == 601) { // Hardware screen (distance)
		onViewingDistanceEvent(pos);
	} else  if (sliderIndex == 602) { // Hardware screen (size)
		onScreenSizeEvent(pos);
	} else  if (sliderIndex == 701) { // Color
		changeColor(pos);
	}
	
}

function showSetup() {
	updateSetupScreenValues();
	$('#setupPanel').show();
}


function showPosition(){
	$('#sliderChoice').empty();
	var choiseTextArray = ["aft", "stb","port", "fwd"];
	var activeChannel;
	
	if(jsonActiveTransceiver.activeCh <0 || jsonActiveTransceiver.activeCh > 4)
		return;
	
	activeChannel = jsonTransceiver.jsonTrans[jsonActiveTransceiver.activeCh];
	
	
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
	var mySlider = new SliderHorizontal(6, "GAIN","%",0, 100, jsonDATA.signal.GAIN, document
			.getElementById("sliderChoice"), gainText, false);

	$('#sliderChoice').show();
}

function showTVG(){
	$('#sliderChoice').empty();

	var tvgText = [ "0%", "20%", "40%", "60%", "80%", "100%" ];
	var mySlider = new SliderHorizontal(7, "TVG","%",0, 100, jsonDATA.signal.TVG, document
			.getElementById("sliderChoice"), tvgText, false);

	$('#sliderChoice').show();
}

function showPOW(){
	$('#sliderChoice').empty();

	var tvgText = [ "0%", "20%", "40%", "60%", "80%", "100%" ];
	var mySlider = new SliderHorizontal(8, "POWER","%",0, 100, jsonDATA.signal.TVG, document
			.getElementById("sliderChoice"), tvgText, false);

	$('#sliderChoice').show();
}

function showFREQ(){
	$('#sliderChoice').empty();

	var tvgText = [ "0%", "20%", "40%", "60%", "80%", "100%" ];
	var mySlider = new SliderHorizontal(9, "FREQ","kHz",0, 100, jsonDATA.signal.TVG, document
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




