
function showScreenSetup(){
	screenShown = true;
	$("#ScreenSetup").show();
}

function removeScreenSetup(){
	screenShown = false;
	$("#ScreenSetup").hide();
}

var depthTypeText=["DBT","DBS","DBK"];
var depthUnitText=["Meter","Feet","Fathoms"];
var depthFontSizeText=["Small","Medium","Large", "Extra"];

function initScreenSetup(){
	var myElem = document.getElementById("ScreenSetup"); 
	
	myElem.innerHTML =
	"<div class='mainTableHeader'>SETUP</div>" +
	"<div id = 'depthTypeChoice' class='screenGroupe'></div>" + 
	"<div id = 'depthUnit' class='screenGroupe'></div>" + 
	"<div id = 'depthFontSize' class='screenGroupe'></div>";
	
	var depthTypeCB= new ChoiceBoxHoriz2(501, "Depth type", getDepthTypeStorage(), document.getElementById("depthTypeChoice"), 3, depthTypeText, "ComBox_A2.png", "ComBox_B2.png", 36,26,180, 50);//144, 50);
	var depthUnitCB = new ChoiceBoxHoriz2(502, "Depth unit", getDepthUnitStorage(), document.getElementById("depthUnit"), 3, depthUnitText, "ComBox_A2.png", "ComBox_B2.png", 36,26,180, 50);//144, 50);
	var depthFontSizeCB = new ChoiceBoxHoriz2(503, "Depth font size", getDepthFontStorage(), document.getElementById("depthFontSize"), 4, depthFontSizeText, "ComBox_A2.png", "ComBox_B2.png", 36,26,240, 50);//144, 50);
	
	$(myElem).click(function(e){
		return preventEv(e);
	});
}

function onDepthTypeCheckboxEvent(newType){ //DBT, DBS, DBK
	setDepthTypeStorage(newType);
	updateDepthTypeText();
}

function onDepthUnitCheckboxEvent(newUnit){ // meter, feet, ...
	setDepthUnitStorage(newUnit);
	updateDepthTypeText();
	changeRange(currRange);
	$("#rangeSliderDiv").empty();
	if(newUnit == 0)
	rangeSlider3 = new SliderVertical(100, "RANGE", 1, 100, 34,
			document.getElementById("rangeSliderDiv"), rangeShownMaxValuesMeter);//testCont"),rangeText);
	else if (newUnit == 1)
		rangeSlider3 = new SliderVertical(100, "RANGE", 1, 100, 34,
				document.getElementById("rangeSliderDiv"), rangeShownMaxValuesFeet);//testCont"),rangeText);
	else if (newUnit == 2)
		rangeSlider3 = new SliderVertical(100, "RANGE", 1, 100, 34,
				document.getElementById("rangeSliderDiv"), rangeShownMaxValuesFathoms);
	
	updateAlarmSlidersText();
}

function onDepthFontEvent(newUnit){
	setDepthFontStorage(newUnit);
	$("#depth").css('font-size', "" + depthFontSizeArr[newUnit] + "px");
	initDepthTypeText();
}

