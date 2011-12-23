var depthTypeText = ["DPT", "DBS","DBA"];

function initDepthText(){
	$("#depth").css('font-size', "80px");
}

function initDepthTypeText(){
	$("#depthType").css('font-size', "30px");
	var test = $("#depth").css('font-size');
	$("#depthType").css('top', (parseInt($("#depth").css('font-size')) + 5) + "px");
}

function updateDepthText(depth){
	document.getElementById("depth").innerHTML = "" + depth + "m";
}

function updateDepthTypeText(){
	document.getElementById("depthType").innerHTML = "" + depthTypeText[getDepthTypeStorage()];
}


