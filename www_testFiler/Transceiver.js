/**
 * 
 */

var channelEnabled = true;
var dualFreqEnabled = false;
var sliderFreq1;
var sliderFreq2;
var enablTransceiverDiv;
var positionsChoiceBox;
var selectedTranscChannel;

function initTransceiver(parentDiv){
	//initMainMenu(parentDiv);
	
	initTransceiverMenu(parentDiv);
	selectTransceiverTabMenu(0, true);
	
	var tabContentDiv = document.createElement("DIV");
	tabContentDiv.id = "tabContentDiv";
	parentDiv.appendChild(tabContentDiv);
	
	
	////////////////////////////////////////////////////////
	// Enabled
	////////////////////////////////////////////////////////
	enablTransceiverDiv = document.createElement("DIV");
	enablTransceiverDiv.id = "enabTranscRadioDiv";
	enablTransceiverDiv.innerHTML="Enable Channel 1<input type=\"checkbox\" id=\"enabTransciver\" onclick=\"onTransciverChanged()\" value=0></input>";
	tabContentDiv.appendChild(enablTransceiverDiv);
	
	var verSpace10 = document.createElement("DIV");
	verSpace10.className = "verSpace10";
	tabContentDiv.appendChild(verSpace10);
	////////////////////////////////////////////////////////
	// Position
	////////////////////////////////////////////////////////
	
	var positBarDiv = document.createElement("DIV");
	positBarDiv.id = "positBarDiv";
	var cTA1 = ["AFT","PORT","STUR","FWD"];
	tabContentDiv.appendChild(positBarDiv);
	
	positionsChoiceBox = new ChoiceBoxHoriz2(202, "Position", 0, document.getElementById("positBarDiv"), 4, cTA1, "Checkbox.png", "CheckboxFull.png", 48,48,400, 80);
	
	verSpace10 = document.createElement("DIV");
	verSpace10.className = "verSpace10";
	tabContentDiv.appendChild(verSpace10);
	////////////////////////////////////////////////////////
	// Frequency 1
	////////////////////////////////////////////////////////
	var freqSlidDiv = document.createElement("DIV");
	freqSlidDiv.className = "freqSlidDiv";
	tabContentDiv.appendChild(freqSlidDiv);
	
	var slidText = [ "20kHz", "40kHz", "60kHz", "80kHz", "100kHz", "120kHz" ];
    sliderFreq1 = new SliderHorizontal(203, "Frequency",2000, 12000, 2000, freqSlidDiv, slidText, false); //jsonDATA.signal.TVG
	
	verSpace10 = document.createElement("DIV");
	verSpace10.className = "verSpace10";
	tabContentDiv.appendChild(verSpace10);
	
   
////////////////////////////////////////////////////////
	// Enabled Frequency 2
	////////////////////////////////////////////////////////
	var enablTransceiverDiv2 = document.createElement("DIV");
	enablTransceiverDiv2.id = "enabTranscRadioDiv2";
	enablTransceiverDiv2.innerHTML="Enable Dual Frequency<input type=\"checkbox\" id=\"enabDual\" onclick=\"onDualFreqEnableChanged()\" value=0></input>";
	tabContentDiv.appendChild(enablTransceiverDiv2);
	
	verSpace10 = document.createElement("DIV");
	verSpace10.className = "verSpace10";
	tabContentDiv.appendChild(verSpace10);
	 ////////////////////////////////////////////////////////
	// Frequency 2
	////////////////////////////////////////////////////////
	var freqSlidDiv2 = document.createElement("DIV");
	freqSlidDiv2.className = "freqSlidDiv";
	tabContentDiv.appendChild(freqSlidDiv2);
	
	//var slidText = [ "22kHz", "20%", "40%", "60%", "60%", "100kHz" ];
	sliderFreq2 = new SliderHorizontal(204, "Frequency 2",2000, 12000, 2000, freqSlidDiv2, slidText, false); //jsonDATA.signal.TVG

	
	
	var disableTranscDiv = document.createElement("DIV");
	disableTranscDiv.id = "disableTranscDiv";
	tabContentDiv.appendChild(disableTranscDiv);
	
	var disableDualFreqDiv = document.createElement("DIV");
	disableDualFreqDiv.id = "disableDualFreqDiv";
	tabContentDiv.appendChild(disableDualFreqDiv);
	
	showChannel(1);
}

function showChannel(channel){
	
		
	if (channel == 1) {
		selectedTranscChannel = jsonTransceiverCH1;
		enablTransceiverDiv.innerHTML="Enable Channel 1<input type=\"checkbox\" id=\"enabTransciver\" onclick=\"onEnableTransciverChanged()\" value=0></input>";	
	} else if(channel == 2) {
		selectedTranscChannel = jsonTransceiverCH2;
		enablTransceiverDiv.innerHTML="Enable Channel 2<input type=\"checkbox\" id=\"enabTransciver\" onclick=\"onEnableTransciverChanged()\" value=0></input>";
	}
	
	dualFreqEnabled = selectedTranscChannel.dualEnabled;
	
	if(selectedTranscChannel.enabled) { 
		enableTransceiver();
		sliderFreq1.setHandlButtValue(selectedTranscChannel.freq1, true);
	}else
		disableTransceiver();
	
	if(selectedTranscChannel.dualEnabled) {
		enableDualFreq();
		sliderFreq2.setHandlButtValue(selectedTranscChannel.freq2, true);
	} else
		disableDualFreq();	
	
	positionsChoiceBox.selectChoice(selectedTranscChannel.position);
}

function onEnableTransciverChanged(){
	if(channelEnabled){
		disableTransceiver();
	} else{
		enableTransceiver();
	}
}

function enableTransceiver(){
	channelEnabled = true;
	$("#disableTranscDiv").hide();
	document.getElementById("enabTransciver").checked = true;
	selectedTranscChannel.enabled=1;
}

function disableTransceiver(){
	channelEnabled = false;
	$("#disableTranscDiv").show();
	document.getElementById("enabTransciver").checked = false;
	selectedTranscChannel.enabled=0;
}

function onDualFreqEnableChanged(){
	if(dualFreqEnabled){
		disableDualFreq();
	} else{
		enableDualFreq();
	}
}

function enableDualFreq(){
	dualFreqEnabled = true;
	$("#disableDualFreqDiv").hide();
	document.getElementById("enabDual").checked = true;
	selectedTranscChannel.dualEnabled=1;
}

function disableDualFreq(){
	dualFreqEnabled = false;
	$("#disableDualFreqDiv").show();
	document.getElementById("enabDual").checked = false;
	selectedTranscChannel.dualEnabled=0;
}
/*
function onSliderMoved(sliderIndex, newValue){
	if(sliderIndex == 202) { 		// Position changed
		selectedTranscChannel.position = newValue;
	} else if(sliderIndex == 203) { // Freq. 1 changed
		selectedTranscChannel.freq1 = newValue;
		sliderFreq1.changeUnderText("Frequency: " + newValue*10 + "kHz");
	} else if(sliderIndex == 204) { // Freq. 2 changed
		selectedTranscChannel.freq2 = newValue;
		sliderFreq2.changeUnderText("Frequency: " + newValue*10 + "kHz");
	}
}*/

