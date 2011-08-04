

// //////////////////////////////
// EchoCanvas class
function Scope(x, y, widgetWidth, widgetHeight) {
	this.frameColor ="#fff";
	this.backgrColor = "#000";
	this.lineColor = "#ffe732";
	this.x = x;
	this.y = y;
	this.test = 1;
	this.widgetWidth = widgetWidth;
	this.widgetHeight = widgetHeight;
	this.scopeDoubleBuffElement = null;
	this.scopeDoubleBuffer2Dcontext = null;
	this.scopeDoubleBuff_1pixData = null;

	this.dataArray = new Array(); // received data

	this.scopeInit();
} // end of constructor

/**
 * public method, class Scope
 */
Scope.prototype.scopeInit = function() {

	this.canvasDoubleBuffElement = document.createElement('canvas');
	this.canvasDoubleBuffElement.width = this.widgetWidth;
	this.canvasDoubleBuffElement.height = this.widgetHeight;

	this.canvasDoubleBuffer2Dcontext = this.canvasDoubleBuffElement
			.getContext('2d');
	
	this.clearBackground();

	/*this.canvasDoubleBuff_1pixData = this.canvasDoubleBuffer2Dcontext
			.createImageData(1, this.widgetHeight);*/
}

/**
 * public method, class Scope
 */
Scope.prototype.clearBackground = function() {
	this.canvasDoubleBuffer2Dcontext.fillStyle = this.backgrColor; 
	this.canvasDoubleBuffer2Dcontext.fillRect(0,0,this.widgetWidth,this.widgetHeight); 
}

/**
 * public method, class Scope
 */
Scope.prototype.paint = function() {
	// clear old pixels
//	this.clearBackground();
	
	// copy the same buffer one pixel left
	//this.canvasDoubleBuffer2Dcontext.drawImage(this.canvasDoubleBuffElement,
	//		-1, 0);
	// TODO: if "createImageData" is not supported by browser, use:
	// "getImageData" (IE9?)
	// var imageData = canvasDoubleBuffer2Dcontext.createImageData(1,
	// nCanasHeight);
	
	
	
	var myCanvasContext = document.getElementById('echoCanvas').getContext('2d');
	
	myCanvasContext.fillStyle = this.frameColor; 
	myCanvasContext.fillRect(0,0,this.widgetWidth +6,400); 
	
	myCanvasContext.fillStyle = this.backgrColor; 
	myCanvasContext.fillRect(0,0,this.widgetWidth,this.widgetHeight); 
	
	myCanvasContext.lineWidth = 1;
	
	
	if (this.dataArray != null) {
		myCanvasContext.strokeStyle = this.lineColor;
		myCanvasContext.beginPath();
		for ( var i = 1; i < 400; i++) { // first byte is deapth
			myCanvasContext.moveTo(i, 256 - this.dataArray[i]);
			myCanvasContext.lineTo(i + 1, 256 - this.dataArray[i+ 1]);
		}
		myCanvasContext.stroke();
		
		// Paint depth (bottom)
		myCanvasContext.beginPath();
		myCanvasContext.strokeStyle = '#fff';;
		myCanvasContext.moveTo(this.dataArray[0], 0);
		myCanvasContext.lineTo(this.dataArray[0], 255);
		
		myCanvasContext.stroke();
		//this.canvasDoubleBuffer2Dcontext.putImageData(
		//		this.canvasDoubleBuff_1pixData, this.canWidth - 1, this.y);

	//	myCanvasContext.drawImage(this.canvasDoubleBuffElement, this.x, this.y);//, this.canWidth,
				//this.canHeight);
		/*document.getElementById('echoCanvas').getContext('2d').font = "bold 36px sans-serif";
		document.getElementById('echoCanvas').getContext('2d').fillText(
				"" + this.test, 10, 30);*/
	} else {
		//TODO: if data has not been received
	}
}

/**
 * Use this after the new data has been received
 */
Scope.prototype.setNewData = function(data) {
	this.dataArray = data;
}
