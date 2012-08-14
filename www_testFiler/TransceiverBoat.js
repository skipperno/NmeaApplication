/**
 * 
 */

var bSigOdd = false;
var botImgType = 2;
var selectedPos= 0;

var boatShown = false;

var butF, butA, butP, butS;
var transcButt;
var butCount = 0;

function showBigBoat(){
	$("#boatBigDiv").show();
	$("#boatBigDiv").empty();
	initBigBoat(document.getElementById("boatBigDiv"));
	boatShown = true;
}

function removeBigBoat(){
	$("#boatBigDiv").empty();
	$("#boatBigDiv").hide();
	
	$("#transButtDiv").empty();
	$("#transButtDiv").hide();
	transcButt = null;
	boatShown = false;
}

function existPosistion(posIndex){
	for(var i = 0; i < 4; i++){
		if(jsonTransceiver.jsonTrans[i].transPos == posIndex && jsonTransceiver.jsonTrans[i].chEnabled)
			return true;
	}
	return false;
}

function initBigBoat(parentDiv){	
	transcButt = new Array();
	
	var actPos = jsonTransceiver.jsonTrans[jsonActiveTransceiver.activeCh].transPos;
	//!!! Button order must be the same as: var cTA1 = ["AFT","STRB","PORT","FWD"]; defined in Transceiver.js
	
	// AFT
	if (existPosistion(0)){ // || actPos == 0) {
		var butAdiv = document.createElement("DIV");
		butAdiv.id = "trans_A";
		parentDiv.appendChild(butAdiv);
		butA = new Button(121, butAdiv, "", "", "sens_NOT.png", "sens_A.png", null, 30, 30, onBigBoatPosClick);
		var textAdiv = document.createElement("DIV");
		textAdiv.id = "transTxt_A";
		parentDiv.appendChild(textAdiv);
	} else 
		butA = null;
	
	// STRUB (right)
	if (existPosistion(1)){ // || actPos == 1) {
		var butSdiv = document.createElement("DIV");
		butSdiv.id = "trans_S";
		parentDiv.appendChild(butSdiv);
		butS = new Button(122, butSdiv, "", "", "sens_NOT.png", "sens_S.png", null, 30, 30, onBigBoatPosClick);
		var textSdiv = document.createElement("DIV");
		textSdiv.id = "transTxt_S";
		parentDiv.appendChild(textSdiv);
	} else 
		butS = null;
	// PORT (left)
	if (existPosistion(2)){ // || actPos == 2) {
		var butPdiv = document.createElement("DIV");
		butPdiv.id = "trans_P";
		parentDiv.appendChild(butPdiv);
		butP = new Button(123, butPdiv, "", "", "sens_NOT.png", "sens_P.png", null, 30, 30, onBigBoatPosClick);
		var textPdiv = document.createElement("DIV");
		textPdiv.id = "transTxt_P";
		parentDiv.appendChild(textPdiv);
	} else 
		butP = null;
	
	// FRONT
	if (existPosistion(3)){ // || actPos == 3) {
		var butFdiv = document.createElement("DIV");
		butFdiv.id = "trans_F";
		parentDiv.appendChild(butFdiv);
		butF = new Button(124, butFdiv, "", "", "sens_NOT.png", "sens_F.png", null, 30, 30, onBigBoatPosClick);
		var textFdiv = document.createElement("DIV");
		textFdiv.id = "transTxt_F";
		parentDiv.appendChild(textFdiv);
	} else
		butF = null;
	
	$(parentDiv).click(function(e){
		return preventEv(e);
	});


	deselectTranscBut();
	showActiveTranscText();
}

function showActiveTranscText(){
	var actPos = jsonTransceiver.jsonTrans[jsonActiveTransceiver.activeCh].transPos;
	
	var tempTxt;
	if (!jsonActiveTransceiver.isActiveDual)
		tempTxt = jsonTransceiver.jsonTrans[jsonActiveTransceiver.activeCh].freq1 + " kHz";
	else 
		tempTxt = jsonTransceiver.jsonTrans[jsonActiveTransceiver.activeCh].freq2 + " kHz";
	
	if(actPos == 0 && butA){
		butA.select();
		document.getElementById("transTxt_A").innerHTML = tempTxt;
	} else if(actPos == 1) {
		butS.select();
		document.getElementById("transTxt_S").innerHTML = tempTxt;
	} else if(actPos == 2){
		butP.select();
		document.getElementById("transTxt_P").innerHTML = tempTxt;
	} else if(actPos == 3){
		butF.select();
		document.getElementById("transTxt_F").innerHTML = tempTxt;
	} 
}

function deselectTranscBut(){
	if(butF){
		butF.deselect();
	} 
	if(butA) {
		butA.deselect();
	} 
	if(butP) {
		butP.deselect();
	} 
	if(butS) {
		butS.deselect();
	}
}

function deselectActiveTranscText(){
	if(butF){
		document.getElementById("transTxt_F").innerHTML = "";
	} 
	if(butA) {
		document.getElementById("transTxt_A").innerHTML = "";
	} 
	if(butP) {
		document.getElementById("transTxt_P").innerHTML = "";
	} 
	if(butS) {
		document.getElementById("transTxt_S").innerHTML = "";
	}
}

//////////////////////////////////////////////////////////////////
// click on circle "port", "forward" ...
//////////////////////////////////////////////////////////////////
function onBigBoatPosClick(butId){ 
	var butInd = butId -120; // because of "new Button(121, ..."
	//???jsonActiveTransceiver.activeCh = butInd - 1;
	
	// changeBoatIconPosition(butInd - 1); //(AFT=0, ...)
	// don't. Wait on button push
	
	butCount = 0;
	$("#transButtDiv").show();
	$("#transButtDiv").empty();
	
	deselectTranscBut();
	
	
	if(butInd == 1 && butA)
		butA.select();
	else if(butInd == 2)
		butS.select();
	else if(butInd == 3)
		butP.select();
	else if(butInd == 4)
		butF.select();
	
	var buttonsDiv = document.getElementById("transButtDiv");
	
	
	var text1;
	var tempDiv;
	
	for(var i = 0; i < 4; i++){
		text1 = "";
		
		if(((jsonTransceiver.jsonTrans[i].transPos + 1) == butInd) && jsonTransceiver.jsonTrans[i].chEnabled){
			if (i > 1) // if extended
				text1 = "EXT CH" + (i + 1 -2);
			else
				text1 = "CH" + (i+1);
			
			transcButt[butCount] = new Button(butCount, buttonsDiv, text1, jsonTransceiver.jsonTrans[i].freq1 + "kHz", "menuItemBackround2.png", "VerMenuItemBackroundSelect2.png", null, 80, 40, onSelectedTransceiverChanged);
			transcButt[butCount].ch=i;
			transcButt[butCount].dual=0;
			
			if (jsonActiveTransceiver.activeCh == i && jsonActiveTransceiver.isActiveDual == 0)
				transcButt[butCount].select();
			butCount++;
			if(jsonTransceiver.jsonTrans[i].dualEnabled == 1){
				if (i > 1) // if extended
					text1 = "DUAL EXT CH" + (i+1-2);
				else
					text1 = "DUAL CH" + (i+1);

				transcButt[butCount] = new Button(butCount, buttonsDiv, text1, jsonTransceiver.jsonTrans[i].freq2 + "kHz", "menuItemBackround2.png", "VerMenuItemBackroundSelect2.png", null, 80, 40, onSelectedTransceiverChanged);
				transcButt[butCount].ch=i;
				transcButt[butCount].dual=1;
				
				if (jsonActiveTransceiver.activeCh == i && jsonActiveTransceiver.isActiveDual == 1)
					transcButt[butCount].select();
				butCount++;
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////
// one of the transceiver buttons (horizontal menu with transc. on this position) is pushed
//////////////////////////////////////////////////////////////////////////////////////////
function onSelectedTransceiverChanged(butId){ 
	deselectActiveTranscText();
	for(var i = 0; i < butCount; i++){
		if (i != butId)
			transcButt[i].deselect();
		else
			transcButt[i].select();
	}
		
	jsonActiveTransceiver.activeCh = transcButt[butId].ch;
	jsonActiveTransceiver.isActiveDual = transcButt[butId].dual;
	showActiveTranscText();
	sendToServer(JSON.stringify(jsonActiveTransceiver)); //TODO: cannot send because of firefox bug
	// Don't change boat icon position. Wait on msg from server (done in index.html)
}



function changeBoatIconPosition(newPos){ 
	var myElement = document.getElementById('boatDiv');  /*7+18 or 27+18 or 35+18 or 55+18*/

		if (newPos == 0){ //"AFT","STRB","PORT","FWD"
			$("#boatDiv").animate({right:'0px'},400);
			//myElement.style.backgroundImage='url(images/Boat_B.png)';
		} else if (newPos == 1){
			$("#boatDiv").animate({right:'33px'},400);
			//myElement.style.backgroundImage='url(images/Boat_CG.png)';
		} else if (newPos == 2){
			$("#boatDiv").animate({right:'33px'},400);
			//myElement.style.backgroundImage='url(images/Boat_CR.png)';
		} else { //if (newPos == 3){
			$("#boatDiv").animate({right:'66px'},400);
			//myElement.style.backgroundImage='url(images/Boat_F.png)';
		}
	
	selectedPos =newPos;
}



