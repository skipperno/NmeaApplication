
var nmeaOutputText=["DPT","DBS","DBA", "PSWP", "XDR"];
var baudRateText=["4800","9600","38400", "115200"];
var displayText=["OUT","IN","OFF"];
var alText=["ON","OFF"];
var nmeaOutputCB;

function showComSetup(){
	comShown = true;
	$("#ComSetup").show();
}

function removeComSetup(){
	comShown = false;
	$("#ComSetup").hide();
}


function initScreenCom(){
	var myElem = document.getElementById("ComSetup"); 
	
	var inOnOff = 2; // select off
	if (selectedIO_source >= 0)
		inOnOff = jsonIO.set[selectedIO_source].outInOff;
	
	myElem.innerHTML =
	"<div id='screanComHeaderText' class='mainTableHeader'>SCREEN COM SETUP</div>" +
	"<div style='width: 185px;position:relative; float:left;'>" +
		"<div id = 'nmeaOutputChoice' class='screenGroupe'></div>" + 
		"<div id = 'baudRateChoice' class='screenGroupe'></div>" + 
		"<div id = 'alarmChoice' class='screenGroupe'></div>" + 
	"</div>" +
	"<div style='width: 280px;position:relative; float:right;'>" +
		"<div id = 'displayChoice' class='screenGroupe'></div>" + 
		"<div id='nmeaOutInText' class='mainTableHeader'>Display NMEA output 2</div>" + 
		"<div id='nmeaListDiv' border='1'>" + 
			"<select id='nmeaList' size='15' multiple='multiple'></select></div>" +
	"</div>";
	
	nmeaOutputCB= new ChoiceBoxMultiple(561, "NMEA OUTPUTS", getDepthTypeStorage(), document.getElementById("nmeaOutputChoice"), 5, nmeaOutputText, "ComBox_A2.png", "ComBox_B2.png", 36,26,180, 50, onOutputsCheckboxEvent);//144, 50);
	var baudRateCB = new ChoiceBoxHoriz2(562, "BAUD RATE", getDepthUnitStorage(), document.getElementById("baudRateChoice"), 4, baudRateText, "ComBox_A2.png", "ComBox_B2.png", 36,26,180, 50, onBaudChanged);//144, 50);
	var alarmCB = new ChoiceBoxHoriz2(564, "ALARM ON/OFF", 0, document.getElementById("alarmChoice"), 2, alText, "ComBox_A2.png", "ComBox_B2.png", 36,26,180, 50, onAlarmChanged);//144, 50);
	var displayCB = new ChoiceBoxHoriz2(563, "", inOnOff, document.getElementById("displayChoice"), 3, displayText, "ComBox_A2.png", "ComBox_B2.png", 36,26,110, 30, onDisplayChanged);//144, 50);
	
	// Select messages (DPT, DBS, ...)
	// TODO: optimize true = 1 false=0
	var selArray = [false,false,false, false, false];
	if (selectedIO_source > -1 && selectedIO_source < 5) {
		for (var i = 0; i < 5; i++) {
			selArray[i] = (jsonIO.set[selectedIO_source].oms[i] == 1); // true or false
		}
		nmeaOutputCB.setSelected(selArray);
	}
	
	$(myElem).click(function(e){
		return preventEv(e);
	});
}

function onOutputsCheckboxEvent(){
	var tempArray = new Array();
	
	for (var i = 0; i < 5; i++){
		if (nmeaOutputCB.choiceSelectedArray[i])
			jsonIO.set[selectedIO_source].oms[i] = 1;
		else
			jsonIO.set[selectedIO_source].oms[i] = 0;
	}

	sendToServer(JSON.stringify(jsonIO.set[selectedIO_source]));
}

//baud rate pushed
function onBaudChanged(selId, selIndex){
	/*jsonBaud.baudR.ba = selIndex;
	sendToServer(JSON.stringify(jsonBaud));
	*/
	jsonIO.set[selectedIO_source].baudR.ba = selIndex;
	sendToServer(JSON.stringify(jsonIO.set[selectedIO_source]));
}

// Changed Displays "Input", "Output" or "Off" 
function onDisplayChanged(selId, selIndex){
	jsonIO.set[selectedIO_source].outInOff = selIndex;
	if(selIndex == 0 || selIndex == 1){
		while(getListCount() > 0) { // TODO: remove all
			removeOptionLast();
		}
	}
		
	sendToServer(JSON.stringify(jsonIO.set[selectedIO_source]));
	if (selIndex == 0)
		document.getElementById("nmeaOutInText").innerHTML = "Sent messages";
	else if (selIndex == 1)
		document.getElementById("nmeaOutInText").innerHTML = "Received messages";
	else
		document.getElementById("nmeaOutInText").innerHTML = "OFF";
}

function onAlarmChanged(selId, selIndex){
	if (selIndex == 0)
		jsonIO.set[selectedIO_source].alOn = 1;
	else
		jsonIO.set[selectedIO_source].alOn = 0;

	sendToServer(JSON.stringify(jsonIO.set[selectedIO_source]));
}



/*
<div id="nmeaPanel">
<form id="nmeaOutputs">
<div class="nmeaHeaderText">NMEA OUTPUTS:</div>
	<table>
	<tr><td width="30px">DPT:</td><td width="45px"><input type="checkbox" id="ch1" name="oms[]" value="a" onclick="onOutputsCheckboxEvent()"></input></td>
	<td width="30px">DBS:</td><td width="45px"><input type="checkbox" id="ch2" name="oms[]" value="b" onclick="onOutputsCheckboxEvent()"></input></td>
	<td width="30px">DBA:</td><td width="45px"><input type="checkbox" id="ch3" name="oms[]" value="c" onclick="onOutputsCheckboxEvent()"></input></td></tr>
	<tr><td width="30px">PSWP:</td><td width="45px"><input type="checkbox" id="ch4" name="oms[]" value="d" onclick="onOutputsCheckboxEvent()"></input></td>
	<td width="30px">XDR</td><td width="45px"><input type="checkbox" id="ch5" name="oms[]" value="e" onclick="onOutputsCheckboxEvent()"></input></td></tr> 
	</table>
</form>



<form id="comBaud">
<div class="nmeaHeaderText">BAUD RATE:</div>
	<table>
	<tr><td width="30px">4800</td><td width="40px"><input type="radio" name="ba" onclick="onBaudChanged(0)" value=0></input></td>
	<td width="30px">9600</td><td width="40px"><input type="radio" name="ba" onclick="onBaudChanged(1)" value=1></input></td>
	<td width="30px">38400</td><td width="40px"><input type="radio" name="ba" onclick="onBaudChanged(2)" value=2></input></td>
	<td width="30px">115200</td><td width="40px"><input type="radio" name="ba" onclick="onBaudChanged(3)" value=3></input></td></tr> 
	</table>
</form>

<form id="diplayForm">
<div class="nmeaHeaderText">DISPLAY</div>
	<table>
	<tr><td width="20px">OUT</td><td width="45px"><input type="radio" name="dis" onclick="onDisplayChanged(0)" value=0></input></td>
	<td width="20px">IN</td><td width="45px"><input type="radio" name="dis" onclick="onDisplayChanged(1)" value=1></input></td>
	<td width="20px">OFF</td><td width="45px"><input type="radio" name="dis" onclick="onDisplayChanged(2)" value=2></input></td></tr> 
	</table>
</form>


<div id="nmeaListDiv" border="1">
	
<select id="nmeaList" size="17" multiple="multiple">
	<!--  	<option value="a" selected="selected">PPSKT, 0200,0,+00.0,0,0050,7,03,*41</option>
			<option value="b">$PPSKT, 0200,0,+00.0,0,0050,7,03,*41</option> -->
</select>
	</div> 
	</div>*/