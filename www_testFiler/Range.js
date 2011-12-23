/**
 * Class Range
 * 
 */
var rangeShown = false;

var arrColor_1 = "#fff";//"#FFE772";//"#FBFF38";
var arrColor_2 = "#000";//#772";
var arrowLength = 556; //TODO: CANVAS_WIDTH; // 30
var myFont = "normal 12px Verdana,\"BitStream vera Sans\",Tahoma,Helvetica,Sans-serif"; //sans-serif

var rangeText = [ /*range: 10m: */ ["0", "2", "4", "6", "8"], 
                  /*range: 50m: */ ["0", "10", "20", "30", "40"], 
                  /*range: 100m:*/ ["0", "20", "40", "60", "80"], 
                  /*range: 500m:*/ ["0", "100", "200", "300", "400"],
                  /*range: 1000m:*/["0", "200", "400", "600", "800"], 
                  /*range: 1600m:*/["0", "320", "640", "960", "1280"] ];
/*
var rangeText = [  ["0", "320", "640", "960", "1280", "1600"], ["0", "200", "400", "600", "800", "1000"], ["0", "100", "200", "300", "400", "500"], 
["0", "20", "40", "60", "80", "100"], ["0", "10", "20", "30", "40", "50"], ["0", "2", "4", "6", "8", "10"]];*/

// !!! Must be same as in file "DataProcessing.cpp"
var rangeMaxValues=[10,50,100,500,1000,1600];//the same values as max values in "rangeText"

var rangePos_Y= [20, 80, 160, 240, 320, 400];

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

function changeRange(range){
	var myElement = document.getElementById('rangeScaleTextDiv');
	var inner="";
	var i = 1;
	
//	inner +="<div class=\"rangeText\" style=\"right:0px;top:0px;\">" + rangeText[range][0] + "</div>";
	
	for(i = 1; i < 5; i++){
		inner +="<div class=\"rangeText\" style=\"right:0px;top:" + (i*80 -8) + "px;\">" + rangeText[range][i] + "</div>";
	}
	//alert(inner);
	myElement.innerHTML=inner;

	/*
	inner +="<div style=\"width:100%; height:20px;float:right; margin:0px;text-align:right; border-top:1px solid #fff\">" + rangeText[range][0] + "</div>";
	inner +="<div style=\"width:100%; height:20px;float:right; margin-top:39px;text-align:right; border-bottom:1px solid #fff\">" + rangeText[range][i] + "</div>";
	
	for(var i = 2; i < 6; i++){
		inner +="<div style=\"width:100%; height:20px;float:right; margin-top:59px;text-align:right; border-bottom:1px solid #fff\">" + rangeText[range][i] + "</div>";
	}
	//alert(inner);
	myElement.innerHTML=inner;*/
	
}


function range_PaintChangedRange(newRange, bufferContex, changedX) {
	if (newRange < 0 || newRange > 5)
		return;
	range_PaintVerticalLine(bufferContex);
	//range_PaintArrowLine_2color(bufferContex, 898, 100, "R:" + newRange);
	var nArrowX = canvasWidth - 2;
	
	
	//range_PaintText_2color(bufferContex,  nArrowX, rangePos_Y[0], rangeText[newRange][0]);
	for(i=1; i<5; i++){
		//range_PaintArrowLine_2color(bufferContex,  nArrowX, rangePos_Y[i], rangeText[newRange][i]);
		range_PaintText_2color(bufferContex, rangePos_Y[i], rangeText[newRange][i]);
	}
	//range_PaintText_2color(bufferContex,  nArrowX, rangePos_Y[5], rangeText[newRange][5]);
	
	bufferContex.fillStyle = "rgba(255, 255, 255, 0.1)";
	bufferContex.fillRect(0,0,CANVAS_WIDTH,CANVAS_HEIGHT);
	/*
	bufferContex.fillStyle = "rgba(255, 255, 255, 0.3)";
	bufferContex.fillRect(0,0,CANVAS_WIDTH,80);
	
	bufferContex.fillStyle = "rgba(255, 255, 255, 0.3)";
	bufferContex.fillRect(0,160,CANVAS_WIDTH,80);
	
	bufferContex.fillStyle = "rgba(255, 255, 255, 0.3)";
	bufferContex.fillRect(0,320,CANVAS_WIDTH,80);*/
	
	/*
	if (newRange == 0) { // 10m range
		range_PaintText_2color(bufferContex,  nArrowX, 20, rangeText[0][0]);
		range_PaintArrowLine_2color(bufferContex, nArrowX, 80, rangeText[0][1]);
		range_PaintArrowLine_2color(bufferContex,  nArrowX, 160, rangeText[0][2]);
		range_PaintArrowLine_2color(bufferContex,  nArrowX, 240, rangeText[0][3]);
		range_PaintArrowLine_2color(bufferContex,  nArrowX, 320, rangeText[0][4]);
		range_PaintText_2color (bufferContex,  nArrowX, 400, rangeText[0][5]);
	} else if (newRange == 1) { // 50 m
		range_PaintText_2color(bufferContex,  nArrowX, 20, rangeText[1][0]);
		range_PaintArrowLine_2color(bufferContex, nArrowX, 80, rangeText[1][1]);
		range_PaintArrowLine_2color(bufferContex,  nArrowX, 160, rangeText[1][2]);
		range_PaintArrowLine_2color(bufferContex,  nArrowX, 240, rangeText[1][3]);
		range_PaintArrowLine_2color(bufferContex,  nArrowX, 320, rangeText[1][4]);
		range_PaintText_2color (bufferContex,  nArrowX, 400, rangeText[1][5]);
	} else if (newRange == 2) {
		range_PaintText_2color(bufferContex,  nArrowX, 20, "0m");
		range_PaintArrowLine_2color(bufferContex, nArrowX, 80, "20m");
		range_PaintArrowLine_2color(bufferContex,  nArrowX, 160, "40m");
		range_PaintArrowLine_2color(bufferContex,  nArrowX, 240, "60m");
		range_PaintArrowLine_2color(bufferContex,  nArrowX, 320, "80m");
		range_PaintText_2color (bufferContex,  nArrowX, 400, "100m");
	} else if (newRange == 3) {
		range_PaintText_2color(bufferContex,  nArrowX, 20, "0m");
		range_PaintArrowLine_2color(bufferContex, nArrowX, 80, "100m");
		range_PaintArrowLine_2color(bufferContex,  nArrowX, 160, "200m");
		range_PaintArrowLine_2color(bufferContex,  nArrowX, 240, "300m");
		range_PaintArrowLine_2color(bufferContex,  nArrowX, 320, "400m");
		range_PaintText_2color (bufferContex,  nArrowX, 400, "500m");
	} else if (newRange == 4) {
		range_PaintText_2color(bufferContex,  nArrowX, 20, "0m");
		range_PaintArrowLine_2color(bufferContex, nArrowX, 80, "200m");
		range_PaintArrowLine_2color(bufferContex,  nArrowX, 160, "400m");
		range_PaintArrowLine_2color(bufferContex,  nArrowX, 240, "600m");
		range_PaintArrowLine_2color(bufferContex,  nArrowX, 320, "800m");
		range_PaintText_2color (bufferContex,  nArrowX, 400, "1000m");
	} else if (newRange == 5) {
		range_PaintText_2color(bufferContex,  nArrowX, 20, "0m");
		range_PaintArrowLine_2color(bufferContex, nArrowX, 80, "320m");
		range_PaintArrowLine_2color(bufferContex,  nArrowX, 160, "640m");
		range_PaintArrowLine_2color(bufferContex,  nArrowX, 240, "960m");
		range_PaintArrowLine_2color(bufferContex,  nArrowX, 320, "1280m");
		range_PaintText_2color (bufferContex,  nArrowX, 400, "1600m");
	}*/
	
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
