/**
 * Class Range
 * 
 */
var oldRange = 0;
var currRange = -1;
	
var rangeShown = false;

var arrColor_1 = "#fff";//"#FFE772";//"#FBFF38";
var arrColor_2 = "#000";//#772";
var arrowLength = 556; //TODO: CANVAS_WIDTH; // 30
var myFont = "normal 12px Verdana,\"BitStream vera Sans\",Tahoma,Helvetica,Sans-serif"; //sans-serif


var rangeMeter = [ [2,4,6,8,10], 
                   [10,20,30,40,50], 
                   [20,40,60,80,100],
                   [100,200,300,400,500],
                   [200,400,600,800,1000], 
                   [300,600,900,1200,1600] ];

//1m = 3.2808399166666664 Feet
var rangeFeet = [  [10,20,30,32.8], 			//32.8 max
                   [50, 100, 150,164],  		// 164 MAX
                   [100,200,300,328],  		// 328
                   [500, 1000, 1500,1640], 	//1640
                   [1000,2000,3000,3280], 		//3280
                   [1000,2000,3000,4000,5248] ]; // 5248

//1m = 0.5468 Fathoms [ftm]
var rangeFathoms = [  [1,2,3,4,5,5.46], 			//32.8 max
                   [5, 10, 15,20,27.3],  		// 164 MAX
                   [10,20,30,40,50,54.6],  		// 328
                   [50, 100, 200,273], 	//1640
                   [100,200,300,400,500,546.8], 		//3280
                   [200,400,500,800,874.8] ]; // 5248



var currentRangeValues; // can be "rangeMeter", "rangeFeet" ...

// !!! Must be same as in file "DataProcessing.cpp" (on the server side)
var rangeMaxValuesCalculation=[10,50,100,500,1000,1600];//!!! used for all calculations

var rangeShownMaxValuesMeter=[10,50,100,500,1000,1600]; //used by range slider
var rangeShownMaxValuesFeet=[30,160,320,1600,3200,5200];//used by range slider
var rangeShownMaxValuesFathoms=[5,25,50,250,500,860];//used by range slider

var unitText = ["m","ft","ftm","?"];
/*
var rangePos_Y		= [20, 80, 160, 240, 320, 400];
var rangePos_Y_feet	= [20, 80, 160, 240, 320, 400];

*/

function initRange() {
	var unit = getDepthUnitStorage();
	if (unit == 0)
		currentRangeValues = rangeMeter;
	else if (unit == 1)
		currentRangeValues = rangeFeet;
	else if (unit == 2)
		currentRangeValues = rangeFathoms;
}

function onRangeButtonOver(){
	
	var myElement = document.getElementById('eastRangeButton');
	myElement.style.backgroundImage='url(images/rangeIconOver2.png)';
}

function onRangeButtonOut(){
	var myElement = document.getElementById('eastRangeButton');
	myElement.style.backgroundImage='url(images/rangeIcon2.png)';
}
	


function onRangeButtonClick(){
	if (rangeShown) {
		removeRangeSlider();
	} else {
		setMenuShown(false);
		$("#rangeSliderDiv").css('left','570px');
		$("#rangeSliderDiv").show();
		$("#rangeSliderDiv").animate({
			left : 20
		}, 500);
		rangeShown = true;
	}
}

function removeRangeSlider(){
	/*$("#rangeSliderDiv").animate({
	left : 570
}, 500);*/
	$("#rangeSliderDiv").hide();
	rangeShown = false;
}

function paintNewRangeLines(newRange){
	$("#rangeScale").empty();
	$("#rangeScaleTextDiv").empty();
	
	var maxValue=currentRangeValues[newRange][currentRangeValues[newRange].length-1]; // the last element is max value and not position (don't paint)
	var resolution = CANVAS_HEIGHT/maxValue; 
	var inner="";
	var tempY;
	
	for (var i=0; i<currentRangeValues[newRange].length - 1; i++) { // the last element is max value and not position (don't paint)
		var newElem = document.createElement("DIV");
		newElem.className="rangeScaleSeg";
		tempY = parseInt(currentRangeValues[newRange][i]*resolution);
		newElem.setAttribute("style", "top:" + tempY + "px");
		$("#rangeScale").append(newElem);
		
		inner +="<div class=\"rangeText\" style=\"right:0px;top:" + (tempY -8) + "px;\">" + currentRangeValues[newRange][i] + "</div>";
	}
	document.getElementById('rangeScaleTextDiv').innerHTML=inner;
}

function changeRange(newRange){
	var unit = getDepthUnitStorage();
	if (unit == 0)
		currentRangeValues = rangeMeter;
	else if (unit == 1)
		currentRangeValues = rangeFeet;
	else if (unit == 2)
		currentRangeValues = rangeFathoms;
	
	if(newRange > -1)
		paintNewRangeLines(newRange);
}


function range_PaintChangedRange(oldRange, bufferContex, changedX) {
	if (oldRange < 0 || oldRange > 5)
		return;
	
	var maxValue=currentRangeValues[oldRange][currentRangeValues[oldRange].length-1]; // the last element is max value and not position (don't paint)
	var resolution = CANVAS_HEIGHT/maxValue; 
	var tempY;
	
	range_PaintVerticalLine(bufferContex);
	//range_PaintArrowLine_2color(bufferContex, 898, 100, "R:" + newRange);
	var nArrowX = canvasWidth - 2;
	
	
	//range_PaintText_2color(bufferContex,  nArrowX, rangePos_Y[0], rangeText[newRange][0]);
	for(i=0; i<currentRangeValues[oldRange].length - 1; i++){
		tempY = parseInt(currentRangeValues[oldRange][i]*resolution);
		//range_PaintArrowLine_2color(bufferContex,  nArrowX, rangePos_Y[i], rangeText[newRange][i]);
		range_PaintText_2color(bufferContex, (tempY +8), currentRangeValues[oldRange][i]);
	}
	//range_PaintText_2color(bufferContex,  nArrowX, rangePos_Y[5], rangeText[newRange][5]);
	
	/*bufferContex.fillStyle = "rgba(255, 255, 255, 0.1)";
	bufferContex.fillRect(0,0,CANVAS_WIDTH,CANVAS_HEIGHT);*/
}

function range_PaintVerticalLine(bufferContex) {
	bufferContex.fillStyle = arrColor_2;
	bufferContex.fillRect(canvasWidth - 3,0,3,canvasHeight);
	
	bufferContex.strokeStyle = arrColor_1;
	bufferContex.beginPath();
	bufferContex.moveTo(canvasWidth - 2, 0);
	bufferContex.lineTo(canvasWidth - 2, canvasHeight);
	bufferContex.stroke();
}


function range_PaintText_2color(bufferContex, posY, valueText) {
	bufferContex.font = myFont;
	
	bufferContex.fillStyle = arrColor_2;
	bufferContex.fillText(valueText, CANVAS_WIDTH -30, posY - 4);
	
	bufferContex.fillStyle = arrColor_1;
	bufferContex.fillText(valueText, CANVAS_WIDTH -29, posY - 5);
}

function range_PaintArrowLine_2color(bufferContex, posX, posY, valueText) {
	range_PaintArrowLine(arrColor_2, bufferContex, posX, posY, valueText);
	range_PaintArrowLine(arrColor_1, bufferContex, posX-1, posY-1, valueText);
}

function range_PaintArrowLine(arrColor, bufferContex, posX, posY, valueText) {
	//bufferContex.font = myFont;
	
	bufferContex.strokeStyle = arrColor;
	bufferContex.beginPath();
	
	bufferContex.moveTo(posX, posY);
	bufferContex.lineTo(posX -arrowLength, posY);
/*	bufferContex.lineTo(posX - arrowLength + 4, posY -4);
	
	bufferContex.moveTo(posX -arrowLength, posY);
	bufferContex.lineTo(posX - arrowLength +4, posY + 4);*/
	bufferContex.stroke();
	
	//bufferContex.fillStyle = arrColor;
	//bufferContex.fillText(valueText, posX -arrowLength, posY - 4);
}
