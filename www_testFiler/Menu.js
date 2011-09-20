var menuShown = false;
var selectedHorizMenuIndex = -1;
var selectedVerticalMenuIndex = 0;

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
		myElement.style.backgroundImage='url(images/MenuShow.png)';
	} else {
		setMenuShown(true);
		onMainMenuClickCallback(selectedVerticalMenuIndex);
		
		myElement.style.backgroundImage='url(images/MenuBack.png)';
	}
}

function onSetupButtonOver() {
	if (!menuShown) {
		var myElement = document.getElementById('menuOnOffBut');
		myElement.style.backgroundImage='url(images/MenuShow_2.png)';
		//myElement.src = "images/MenuShow_2.png";
	}
}
function onSetupButtonOut() {
	if (!menuShown) {
		var myElement = document.getElementById('menuOnOffBut');
		myElement.style.backgroundImage='url(images/MenuShow.png)';
		//myElement.src = "images/MenuShow.png";
	}
}

function setMenuShown(show) {
	if (show) {
		showHorizontalMenu(0);
		$(vertMenuSliding).show();
	} else {
		showHorizontalMenu(-1);
		$(vertMenuSliding).hide();
		$('#sliderChoice').empty();
		$('#sliderChoice').hide();
	}
	menuShown = show;
}


/** ******************************************** */
/** *******         Callback              ****** */
/** ******************************************** */
function onMainMenuClickCallback(menuIndex) {
	selectVerticalMenu(menuIndex);
	showHorizontalMenu(menuIndex);
	selectedVerticalMenuIndex = menuIndex;
}

function onHorisontalMenuCallback(menuIndex, pushed) {
	/*if (!pushed) { // the same button released
		$('#sliderChoice').empty();
		
		if (selectedHorizMenuIndex == menuIndex) {// the same button
			selectHorizontalMenu(-1);
			selectedHorizMenuIndex = -1;
			$('#sliderChoice').hide();
			return;
		}
		
	}*/
	
	// TODO: save?
	
	if (pushed) {
		if (selectedHorizMenuIndex > -1) { // other button was pushed 
			
		}
		selectedHorizMenuIndex = menuIndex;
	} else {
		selectedHorizMenuIndex = -1;
		$('#sliderChoice').hide();
	}
	
	switch(menuIndex){
	case 0:
		if (pushed)
			showAlarm_L();  
		else
			$('#sliderChoice').empty();
		break;
	case 1:
		if (pushed)
			showAlarm_H(); 
		else
			$('#sliderChoice').empty();
		break;
	/*case 2: //MARK
		if (pushed)
			showPosition();
		else
			$('#sliderChoice').empty();
		break;*/
	case 3: //POSITION
		if (pushed)
			showPosition();
		else
			$('#sliderChoice').empty();
		break;
	/*case 4: //DRAUGHT
		if (pushed)
			// 
		else
			$('#sliderChoice').empty();
		break;*/
		
	case 5: //MODE
		/*if (pushed)
			showAlarm_L();
		else
			$('#sliderChoice').empty();
		break;*/
	case 6: // GAIN
		if (pushed)
			showGain();
		else
			$('#sliderChoice').empty();
		break;
	case 7: // TVG
		if (pushed)
			showTVG();
		else
			$('#sliderChoice').empty();
		break;
	case 8: // PWR
		if (pushed)
			showPOW();
		else
			$('#sliderChoice').empty();
		break;
	case 9: // FREQ
		if (pushed)
			showFREQ();
		else
			$('#sliderChoice').empty();
		break;
	case 10: //COM1
		selectedIO_source = 2; // COM2
		nmeaIO_PanelPopulate();
		
		if (pushed) {
			$("#nmeaPanel").show();
		} else {
			$("#nmeaPanel").hide();
		}
		break;
	case 11: //COM2
		selectedIO_source = 3; // COM3
		nmeaIO_PanelPopulate();
		
		if (pushed) {
			$("#nmeaPanel").show();
		} else {
			$("#nmeaPanel").hide();
		}
		break;
		
	case 12: //LAN // !!! Now is Green-Blue
		selectedIO_source = 4; // LAN
		nmeaIO_PanelPopulate();
		
		if (pushed) {
			changeToGreen();
		} else {}
		break;
	case 13: //CAN //!!! Now is Scope
		selectedIO_source = 5; // CAN
		if (pushed) {
			changeHorMenuButtonValue(menuIndex, "On");
			changeToScopeScreen();
		} else {
			changeHorMenuButtonValue(menuIndex, "Off");
			changeToEchoScreen();
		}
		break;
	case 14: 
		if (pushed) {
			showParity();
		} else {$('#sliderChoice').empty();}
		break;
		/*   SCOPE
		 if (pushed) {
			changeHorMenuButtonValue(menuIndex, "On");
			changeToScopeScreen();
		} else {
			changeHorMenuButtonValue(menuIndex, "Off");
			changeToEchoScreen();
		}
		break;
		 */
		
		/*  GREEN/BLUE
		  if (pushed) {
			changeToGreen();
		} else {}
		break;
		 */
		
	default:
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
		changeSignalBeamIconPos(4 - pos);
		//"fwd", "port", "stb", "aft"
		if(pos == 0) 
			menuArray[3].changeValueText("fwd");
		else if(pos == 1) 
			menuArray[3].changeValueText("port");
		else if(pos == 2) 
			menuArray[3].changeValueText("stb");
		else if(pos == 3) 
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
	} else if (sliderIndex == 100){ 
		changeTimeRange(pos); 
	} else if (sliderIndex == 101) {
		changeRange(pos); 
	} else if (sliderIndex == 51) { // BRIGHTNES
		onBrightnes(pos);  // defined in Light.js
	} else if (sliderIndex == 52) { // LIGHT PRESETS
		onLightPresets(pos); 
	} else if (sliderIndex == 53) { // DAY/NIGHT
		onDayNight(pos); 
	}

}

function showAlarm_L(){
	$('#sliderChoice').empty();

	var alarmText = [ "0m", "320m", "640m", "960m", "1280m", "1600m" ];
	var mySlider = new SliderHorizontal(0, "Alarm Shallow",0, 1600, jsonDATA.alarm.L, document
			.getElementById("sliderChoice"), alarmText, false);

	$('#sliderChoice').show();
}

function showAlarm_H(){
	$('#sliderChoice').empty();

	var alarmText = [ "0m", "320m", "640m", "960m", "1280m", "1600m" ];
	var mySlider = new SliderHorizontal(1, "Alarm Deep",0, 1600, jsonDATA.alarm.H, document
			.getElementById("sliderChoice"), alarmText, false);

	$('#sliderChoice').show();
}

function showPosition(){
	$('#sliderChoice').empty();
	var choiseTextArray = ["fwd", "port", "stb", "aft"];
	
	var testChoice = new ChoiceBoxHoriz2(3, "Position", 1, document.getElementById("sliderChoice"), 4, choiseTextArray, "Checkbox.png", "CheckboxFull.png", 48,48,400, 90);

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




