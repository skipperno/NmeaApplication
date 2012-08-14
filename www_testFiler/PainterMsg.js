
var imageMsgObj;

function paintMsgLine(drawingContex, posX){
	
}

function paintMsgLine3px(drawingContex, posX, height, textLine1, textLine2, textLine3){
	if (imageMsgObj == null){
		imageMsgObj = new Image();
		imageMsgObj.src = "images/msg2.png";
	}
	//drawingContex.font = "bold 14px sans-serif";
	drawingContex.font = "14px sans-serif";
	drawingContex.fillStyle = "#f00";
	drawingContex.fillRect(posX - 2,0,3,height);
	
	drawingContex.strokeStyle = "#0f0";
	drawingContex.beginPath();
	drawingContex.moveTo(posX - 1, 0);
	drawingContex.lineTo(posX - 1, height);
	drawingContex.stroke();
	
	
	
    drawingContex.drawImage(imageMsgObj,posX - 102,height - 80);
    
	//drawingContex.fillStyle = "#fff";
	//drawingContex.fillRect(posX - 80,height - 64,77,40);
	
	
    drawingContex.fillStyle = "#666";
	drawingContex.fillText(textLine1, posX -84, height - 65);
	drawingContex.fillStyle = "#ccc";
	drawingContex.fillText(textLine2, posX -67, height - 45);
	drawingContex.fillText(textLine3, posX -67, height - 25);
}