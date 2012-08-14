
var depthUnit = ["m", "ft","ftm"];
var depthConverFactor = [1, 3.28, 0.5468];
var depthFontSizeArr;// = [20,50,90,140]; // !!! "index.html"

function initDepthText(){
	depthFontSizeArr=new Array();
	recalculateFontSize();
	$("#depth").css('font-size', "" + depthFontSizeArr[getDepthFontStorage()] + "px");
}

function initDepthTypeText(){
	//$("#depthType").css('font-size', "20px");
	//var test = $("#depth").css('font-size');
	//$("#depthType").css('top', (parseInt($("#depth").css('font-size')) + 5) + "px");
}



function updateDepthText(depth){
	document.getElementById("depth").innerHTML = "" + depth;
}

function updateDepthTypeText(){ 
	document.getElementById("depthType").innerHTML = "" + depthTypeText[getDepthTypeStorage()] + " [" + depthUnit[getDepthUnitStorage()] + "]";
}

function updateDepthRightText(depth) {
	document.getElementById("depthRight").innerHTML = "" + parseInt(depth);
	var alarmState = getAlarmState();
	if (alarmConfirmed == 0){
		if (alarmState == 0)
			$("#depthRight").css('color','#FFFFFF');
		else
			$("#depthRight").css('color','#FF0000');
		
		$("#depthRight").css("backgroundColor", "#444");  // TODO: optimize, don't change if color is red
    }

		
	$("#depthRight").css('top','' + (bottomPoint - 8) + 'px');
}



