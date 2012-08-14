var channelEnabled = true;
var dualFreqEnabled = false;
var sliderFreq1;
var sliderFreq2;
var enablTransceiverDiv;
var enablTransceiverTextDiv;
var enabTranscButt;
var enabDualFreqButt;
var positionsChoiceBox;
var selectedTranscChannel;
var cTA1 = ["AFT","STRB","PORT","FWD"];


//////////////////////////////////////////////////
// User events
//////////////////////////////////////////////////
function onEnableTransceiver(buttId, selected){
	onEnableTransciverChanged(selected);
	sendTransceiverData();
}

function onEnableDualFreq(buttId, selected){
	onDualFreqEnableChanged();//selected);
	sendTransceiverData();
}

function onTransPosChanged(newPos){
	selectedTranscChannel.transPos = newPos;
	sendTransceiverData();
}

function onFreqSliderMoved(dual, newValue){
	if(dual) {
		selectedTranscChannel.freq2 = newValue;
		sliderFreq2.changeUnderText("Frequency: " + newValue + "kHz");
	} else { // Freq. 1 changed
		selectedTranscChannel.freq1 = newValue;
		sliderFreq1.changeUnderText("Frequency: " + newValue + "kHz");
	}
	
	sendTransceiverData();
}

//////////////////////////////////////////////////

function onEnableTransciverChanged(enab){
	channelEnabled = enab;
	
	if(channelEnabled){
		enableTransceiver();
	} else{
		disableTransceiver();
	}
}

function onDualFreqEnableChanged(){
	if(dualFreqEnabled){
		disableDualFreq();
	} else{
		enableDualFreq();
	}
}

function initTransceiver(parentDiv){
	initTransceiverMenu(parentDiv);
	selectTransceiverTabMenu(0);
	
	var tabContentDiv = document.createElement("DIV");
	tabContentDiv.id = "tabContentDiv";
	parentDiv.appendChild(tabContentDiv);
	
	$(parentDiv).click(function(e){
		return preventEv(e);
	});
	
	
	////////////////////////////////////////////////////////
	// Enabled
	////////////////////////////////////////////////////////
	enablTransceiverDiv = document.createElement("DIV");
	enablTransceiverDiv.className = "enabTranscRadioDiv";
	
	enablTransceiverTextDiv = document.createElement("DIV");
	enablTransceiverTextDiv.className="enabTranTextClass";
	enablTransceiverTextDiv.id = "enablTransceiverTextDiv";
	
	enablTransceiverTextDiv.innerHTML = "Enable Channel 1";
	
	enablTransceiverDiv.appendChild(enablTransceiverTextDiv);
	tabContentDiv.appendChild(enablTransceiverDiv);

	enabTranscButt = new Button(1, enablTransceiverDiv, "", "", "chBox_30_not_sel.png", "chBox_30_sel.png", null, 20, 20, onEnableTransceiver);
	
	
	
	
	var verSpace10 = document.createElement("DIV");
	verSpace10.className = "verSpace10";
	tabContentDiv.appendChild(verSpace10);
	////////////////////////////////////////////////////////
	// Position
	////////////////////////////////////////////////////////
	
	var positBarDiv = document.createElement("DIV");
	positBarDiv.id = "positBarDiv";
	
	tabContentDiv.appendChild(positBarDiv);
	
	positionsChoiceBox = new ChoiceBoxHoriz2(202, "Position", 0, document.getElementById("positBarDiv"), 4, cTA1, "Checkbox2.png", "CheckboxFull.png", 48,48,400, 80);
	
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
    sliderFreq1 = new SliderHorizontal(203, "Frequency","kHz",20, 120, 30, freqSlidDiv, slidText, false); //jsonDATA.signal.TVG
	
	verSpace10 = document.createElement("DIV");
	verSpace10.className = "verSpace10";
	tabContentDiv.appendChild(verSpace10);
	
   
////////////////////////////////////////////////////////
	// Enabled Frequency 2
	////////////////////////////////////////////////////////
	var enablTransceiverDiv2 = document.createElement("DIV");
	enablTransceiverDiv2.className = "enabTranscRadioDiv";
	//enablTransceiverDiv2.innerHTML="Enable Dual Frequency<input type=\"checkbox\" id=\"enabDual\" onclick=\"onDualFreqEnableChanged()\" value=0></input>";	
	tabContentDiv.appendChild(enablTransceiverDiv2);
	var enablDualTextDiv = document.createElement("DIV");
	enablDualTextDiv.className="enabTranTextClass";
	enablDualTextDiv.id = "enablDualTextDiv";
	enablDualTextDiv.innerHTML = "Enable Dual Frequency";
	enablTransceiverDiv2.appendChild(enablDualTextDiv);
	
	enabDualFreqButt = new Button(1, enablTransceiverDiv2, "", "", "chBox_30_not_sel.png", "chBox_30_sel.png", null, 20, 20, onEnableDualFreq);
	//enablTransceiverDiv2.appendChild(enabDualFreqButt);
	
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
	sliderFreq2 = new SliderHorizontal(204, "Frequency 2","kHz",20, 120, 50, freqSlidDiv2, slidText, false); //jsonDATA.signal.TVG

	
	
	var disableTranscDiv = document.createElement("DIV");
	disableTranscDiv.id = "disableTranscDiv";
	tabContentDiv.appendChild(disableTranscDiv);
	
	var disableDualFreqDiv = document.createElement("DIV");
	disableDualFreqDiv.id = "disableDualFreqDiv";
	tabContentDiv.appendChild(disableDualFreqDiv);
	
	//showChannel(0);
}

function showChannel(channel){
	if (channel == 0) {
		selectedTranscChannel = jsonTransceiver.jsonTrans[0];
		enablTransceiverTextDiv.innerHTML="Enable Channel 1";
	} else if(channel == 1) {
		selectedTranscChannel = jsonTransceiver.jsonTrans[1];
		enablTransceiverTextDiv.innerHTML="Enable Channel 2";
	} else if(channel == 2) {
		selectedTranscChannel = jsonTransceiver.jsonTrans[2];
		enablTransceiverTextDiv.innerHTML="Enable Extended Channel 1";
	} else if(channel == 3) {
		selectedTranscChannel = jsonTransceiver.jsonTrans[3];
		enablTransceiverTextDiv.innerHTML="Enable Extended Channel 2";	
	}
	else
		alert("Channel:" + channel);
	
	
	dualFreqEnabled = selectedTranscChannel.dualEnabled;
	
	if(selectedTranscChannel.chEnabled) { 
		enableTransceiver();
		sliderFreq1.setHandlButtValue(selectedTranscChannel.freq1, true);
	}else
		disableTransceiver();
	
	if(selectedTranscChannel.dualEnabled) {
		enableDualFreq();
		sliderFreq2.setHandlButtValue(selectedTranscChannel.freq2, true);
	} else
		disableDualFreq();	
	
	positionsChoiceBox.selectChoice(selectedTranscChannel.transPos);
}

function enableTransceiver(){
	channelEnabled = true;
	$("#disableTranscDiv").hide();
	enabTranscButt.select();
	//document.getElementById("enabTransciver").checked = true;
	selectedTranscChannel.chEnabled=1;
}

function disableTransceiver(){
	channelEnabled = false;
	$("#disableTranscDiv").show();
	enabTranscButt.deselect();
	//document.getElementById("enabTransciver").checked = false;
	selectedTranscChannel.chEnabled=0;
}



function enableDualFreq(){
	dualFreqEnabled = true;
	$("#disableDualFreqDiv").hide();
	enabDualFreqButt.select();
	selectedTranscChannel.dualEnabled=1;
}

function disableDualFreq(){
	dualFreqEnabled = false;
	$("#disableDualFreqDiv").show();
	enabDualFreqButt.deselect();
	selectedTranscChannel.dualEnabled=0;
}

function sendTransceiverData(){
	//var teee = JSON.stringify(jsonTransceiver);
	//alert(teee);
	//TODO: BUG in Firefox? if sending "jsonTransceiver" (long msg), data corrupt.
	sendToServer(JSON.stringify(selectedTranscChannel));//jsonTransceiver));
}


