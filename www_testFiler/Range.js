/**
 * Class Range
 * 
 */
var arrColor_1 = "#fff";//"#FFE772";//"#FBFF38";
var arrColor_2 = "#000";//#772";
var arrowLength = 30;
var myFont = "normal 12px Verdana,\"BitStream vera Sans\",Tahoma,Helvetica,Sans-serif"; //sans-serif

var rangeText = [  ["0", "320", "640", "960", "1280", "1600"], ["0", "200", "400", "600", "800", "1000"], ["0", "100", "200", "300", "400", "500"], 
["0", "20", "40", "60", "80", "100"], ["0", "10", "20", "30", "40", "50"], ["0", "2", "4", "6", "8", "10"]];

var rangePos_Y= [20, 80, 160, 240, 320, 400];


function changeRange(range){
	var myElement = document.getElementById('rangeScale');
	var inner="";
	var i = 1;

	
	inner +="<div style=\"width:100%; height:20px;float:right; margin:0px; color:#fff; border-top:1px solid #fff\">" + rangeText[range][0] + "</div>";
	inner +="<div style=\"width:100%; height:20px;float:right; margin-top:39px; color:#fff; border-bottom:1px solid #fff\">" + rangeText[range][i] + "</div>";
	
	for(var i = 2; i < 6; i++){
		inner +="<div style=\"width:100%; height:20px;float:right; margin-top:59px; color:#fff; border-bottom:1px solid #fff\">" + rangeText[range][i] + "</div>";
		//inner +="<div>" + rangeText[currRange][i] + "<img src=\"images/range.png\" height:\"3px\" style=\"float:right; margin-top:" + 80 + "px\" /></div>";
	}
	//alert(inner);
	myElement.innerHTML=inner;
	
}


function range_PaintChangedRange(newRange, bufferContex, changedX) {
	range_PaintVerticalLine(bufferContex, changedX);
	//range_PaintArrowLine_2color(bufferContex, 898, 100, "R:" + newRange);
	var nArrowX = canvasWidth - 2;
	
	
	range_PaintText_2color(bufferContex,  nArrowX, rangePos_Y[0], rangeText[newRange][0]);
	for(i=1; i<5; i++){
		range_PaintArrowLine_2color(bufferContex,  nArrowX, rangePos_Y[i], rangeText[newRange][i]);
		range_PaintText_2color(bufferContex,  nArrowX, rangePos_Y[i], rangeText[newRange][i]);
	}
	range_PaintText_2color(bufferContex,  nArrowX, rangePos_Y[5], rangeText[newRange][5]);
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

function range_PaintVerticalLine(bufferContex, changedX) {
	bufferContex.fillStyle = arrColor_2;
	bufferContex.fillRect(canvasWidth - 3,0,3,canvasHeight);
	
	bufferContex.strokeStyle = arrColor_1;
	bufferContex.beginPath();
	bufferContex.moveTo(canvasWidth - 2, 0);
	bufferContex.lineTo(canvasWidth - 2, canvasHeight);
	bufferContex.stroke();
}


function range_PaintText_2color(bufferContex, posX, posY, valueText) {
	bufferContex.font = myFont;
	
	bufferContex.fillStyle = arrColor_2;
	bufferContex.fillText(valueText, posX -arrowLength, posY - 4);
	
	bufferContex.fillStyle = arrColor_1;
	bufferContex.fillText(valueText, posX -arrowLength -1, posY - 5);
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
	bufferContex.lineTo(posX - arrowLength + 4, posY -4);
	
	bufferContex.moveTo(posX -arrowLength, posY);
	bufferContex.lineTo(posX - arrowLength +4, posY + 4);
	bufferContex.stroke();
	
	//bufferContex.fillStyle = arrColor;
	//bufferContex.fillText(valueText, posX -arrowLength, posY - 4);
}
