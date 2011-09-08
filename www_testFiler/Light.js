var lightPanelShown = false;
var sliderBrightnes;
var lightPresets;
var dayNight;
var isDay = true;
var presetsSelectLev = 0;

function onLightButtonOver(){
	var myElement = document.getElementById('eastLightButton');
	myElement.style.backgroundImage='url(images/contrast_48_Over.png)';
}

function onLightButtonOut(){
	var myElement = document.getElementById('eastLightButton');
	myElement.style.backgroundImage='url(images/contrast_48.png)';
}
	
function onLightButtonClick(){
	if(lightPanelShown){
		$("#day_night").hide();
		lightPanelShown = false;
	} else {
		$("#day_night").show();
		lightPanelShown = true;
	}
}



function createLightDiv(parentDiv){
	var lightSliderDiv;
	var lightStepDiv;
	var lightDay_NightDiv;
	
	lightSliderDiv = document.createElement("DIV");
	lightSliderDiv.id = "lightSliderDiv";
	
	lightPresetDiv = document.createElement("DIV"); 
	lightPresetDiv.id = "lightPresetDiv";
	
	lightDay_NightDiv = document.createElement("DIV"); 
	lightDay_NightDiv.id = "lightDay_NightDiv";
	
	parentDiv.appendChild(lightSliderDiv);
	parentDiv.appendChild(lightPresetDiv);
	parentDiv.appendChild(lightDay_NightDiv);
	
	var slidText = [ "0%", "20%", "40%", "60%", "80%", "100%" ];
	sliderBrightnes = new SliderHorizontal(51, "Brightness",0, 100, jsonLIGHT.brighDay[0], document
			.getElementById("lightSliderDiv"), slidText, false); //jsonDATA.signal.TVG
	
	
	var cTA1 = ["1","2","3","4","5"];
	lightPresets = new ChoiceBoxHoriz2(52, "Presets", 0, document.getElementById("lightPresetDiv"), 5, cTA1, "but.png", "but_push.png", 70,70,400, 90);
	//ChoiceBoxHoriz2(choiceIndex, shownText, selectedIndex, parentContainer, choiceCount, choiceNamesArray, cssNomal, cssSelect, iconWidth, iconHeight, totWidth)
	//var testChoice = new ChoiceBoxHoriz(52, "???", 0, document.getElementById("lightPresetDiv"), 5, cTA1);

	
	var cTA2 = [ "Day", "Night"];
	//var testChoice = new ChoiceBoxHoriz(53, "", 0, document.getElementById("lightDay_NightDiv"), 2, cTA2);
	dayNight = new ChoiceBoxHoriz2(53, "", 0, document.getElementById("lightDay_NightDiv"), 2, cTA2, "but2.png", "but_push2.png", 150,70,400,90);
}

///////// CALLBACK ////////////////
function onBrightnes(pos){
	if (isDay)
		jsonLIGHT.brighDay[presetsSelectLev] = pos;
	else
		jsonLIGHT.brighNight[presetsSelectLev] = pos;
}
function onLightPresets(pos){
	if (isDay)
		sliderBrightnes.setHandlButtValue(jsonLIGHT.brighDay[pos], true);
	else
		sliderBrightnes.setHandlButtValue(jsonLIGHT.brighNight[pos], true);
	
	presetsSelectLev = pos;
}
function onDayNight(pos){
	if (pos == 0) {
		isDay = true;
		sliderBrightnes.setHandlButtValue(jsonLIGHT.brighDay[presetsSelectLev], true);
	} else {
		isDay = false;
		sliderBrightnes.setHandlButtValue(jsonLIGHT.brighNight[presetsSelectLev], true);
	}
}