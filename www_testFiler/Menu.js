var menuShown = false;
var selectedHorizMenuIndex = -1;

function onHorisontalMenuCallback(menuIndex) {
	if (selectedHorizMenuIndex > -1) {
		$('#sliderChoice').empty();
		
		if (selectedHorizMenuIndex == menuIndex) {// the same button
			selectHorizontalMenu(-1);
			selectedHorizMenuIndex = -1;
			$('#sliderChoice').hide();
			return;
		}
		// TODO: save?
	}

	selectedHorizMenuIndex = menuIndex;
	
	switch(menuIndex){
	case 0:
		showGain();
		break;
	case 1:
		showTVG();
		break;
	case 11:
		changeToGreen();
		break;
	default:
		alert("NOT IMPELMENTED");
		break;
	}

	
	selectHorizontalMenu(menuIndex);
}

function onMainMenuClickCallback(menuIndex) {
	selectVerticalMenu(menuIndex);
	showHorizontalMenu(menuIndex);
}

function onSliderMoved(sliderIndex, pos) {
	if (sliderIndex >= 0 && sliderIndex < 3) {    //GAIN, TVG or POWER
		 //menuArray[sliderIndex].changeValueText(""+pos+"%"); // don't. Wait on new values from server
		 if (pos >= 0 && pos <= 100) {
			 if (sliderIndex == 0)
				 jsonDATA.signal.GAIN=pos;
			 else if (sliderIndex == 1)
				 jsonDATA.signal.TVG=pos;
			 else
				 jsonDATA.signal.POW=pos;
			 sendToServer(JSON.stringify(jsonDATA));
		 }
			 
		 else
			 alert("onSliderMoved Error value: " + pos);
	}	 
	/* if (sliderIndex == 0) {    //GAIN
		 menuArray[0].changeValueText(""+pos+"%");
		 if (pos >= 0 && pos <= 100) {
			 //sendToServer("G" + pos);
			 jsonGAIN.signal.GAIN=pos;
			 sendToServer(JSON.stringify(jsonGAIN));//jsonGAIN.toJSONString());
			 jsonDATA.signal.GAIN=pos; // TODO: save or get from server?
		 }
			 
		 else
			 alert("Gain Error: " + pos);
	 } else if (sliderIndex == 1) {    //GAIN
		 menuArray[1].changeValueText(""+pos+"%");
		 if (pos >= 0 && pos <= 100) {
			// jsonGAIN.signal.TVG=pos;
			// sendToServer(JSON.stringify(jsonGAIN));//jsonGAIN.toJSONString());
			 jsonDATA.signal.TVG=pos; // TODO: save or get from server?
		 }
			 
		 else
			 alert("TVG Error: " + pos);
	 } */else if (sliderIndex == 100){ 
		 changeTimeRange(pos); 
	} else if (sliderIndex == 101) {
		changeRange(pos); 
	}

}

function showGain() {
	$('#sliderChoice').empty();

	var gainText = [ "0%", "20%", "40%", "60%", "80%", "100%" ];
	var mySlider = new SliderHorizontal(0, "GAIN",0, 100, jsonDATA.signal.GAIN, document
			.getElementById("sliderChoice"), gainText, false);

	$('#sliderChoice').show();
}

function showTVG(){
	$('#sliderChoice').empty();

	var tvgText = [ "0%", "20%", "40%", "60%", "80%", "100%" ];
	var mySlider = new SliderHorizontal(1, "TVG",0, 100, jsonDATA.signal.TVG, document
			.getElementById("sliderChoice"), tvgText, true);

	$('#sliderChoice').show();
}

function onSetupButtonClick() {
	var myElement = document.getElementById('enbMenuBut');

	if (menuShown) {
		$("#rangeSliderDiv").animate({
			left : 570
		}, 500);
		setMenuShown(false);
		myElement.src = "images/menu.png";
	} else {
		$("#rangeSliderDiv").animate({
			left : 20
		}, 500);
		setMenuShown(true);
		myElement.src = "images/go-back-icon_black.png";
	}
}

function initMenu() {

	initHorisontalSubMenu();
	setMenuShown(false);
}

/** ******************************************** */
/** ******* Button Setup/Exit Menu ****** */
/** ******************************************** */
function onSetupButtonOver() {
	if (!menuShown) {
		var myElement = document.getElementById('enbMenuBut');
		myElement.src = "images/menu_foc.png";
	}
}
function onSetupButtonOut() {
	if (!menuShown) {
		var myElement = document.getElementById('enbMenuBut');
		myElement.src = "images/menu.png";
	}
}

function setMenuShown(show) {
	if (show) {
		showHorizontalMenu(0);
		$(vertMenuSliding).show();
	} else {
		showHorizontalMenu(-1);
		$(vertMenuSliding).hide();
	}
	menuShown = show;
}
