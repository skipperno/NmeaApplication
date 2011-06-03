var noOfColors = 19; // !!! set this number to length of your color array

// DON'T REMOVE. This is array for green color
/*var colors_R = new Array(0x00, 0x00, 0x09, 0x0D, 0x1C, 0x29, 0x38, 0x5C, 0x8C, 0xAC);
 var colors_G = new Array(0x00, 0x25, 0x40, 0x5E, 0x6D, 0x9D, 0xBE, 0xFF, 0xFF, 0xFF);
 var colors_B = new Array(0x00, 0x00, 0x09, 0x0D, 0x1C, 0x29, 0x38, 0x5C, 0x8C, 0xAC);
 */

var colors_R = new Array(40, 80, 40, 0, 0, 0, 0, 0, 40, 120, 200, 240, 252,
		224, 180, 160, 120, 80, 40);
var colors_G = new Array(252, 220, 140, 80, 40, 0, 80, 120, 160, 200, 200, 240,
		200, 120, 80, 0, 0, 0, 0);
var colors_B = new Array(252, 220, 192, 168, 160, 128, 64, 40, 0, 0, 0, 0, 0,
		0, 0, 20, 40, 20, 0);

// //////////////////////////////
// EchoCanvas class
function EchoCanvas(canWidth, canHeight) {
	this.canWidth = canWidth;
	this.canHeight = canHeight;
	this.canvasDoubleBuffElement = null;
	this.canvasDoubleBuffer2Dcontext = null;
	this.canvasDoubleBuff_1pixData = null;

	this.colorArray = new Array();

	this.colorStartIndex;
	this.colorRest;

	
	this.echoPainter_init();
} // end of class

// public methode, class EchoCanvas
EchoCanvas.prototype.echoPainter_init = function() {

	this.canvasDoubleBuffElement = document.createElement('canvas');
	this.canvasDoubleBuffElement.width = this.canWidth + 20; // 20 pix if
																// painting 20
																// times in one
																// sec.(sleep
																// 50ms)
	this.canvasDoubleBuffElement.height = this.canHeight;

	this.canvasDoubleBuffer2Dcontext = this.canvasDoubleBuffElement
			.getContext('2d');
	this.canvasDoubleBuff_1pixData = this.canvasDoubleBuffer2Dcontext
			.createImageData(1, this.canHeight);
}

/**
 * public method, class EchoCanvas
 */
EchoCanvas.prototype.echoPainter_PaintCanvas = function() {
	this.canvasDoubleBuffer2Dcontext.drawImage(this.canvasDoubleBuffElement,
			-1, 0);
	// TODO: if "createImageData" is not supported by browser, use:
	// "getImageData" (IE9?)
	// var imageData = canvasDoubleBuffer2Dcontext.createImageData(1,
	// nCanasHeight);

	for ( var i = 0; i < 400; i++) {
		this.interpolateColorIndex(this.colorArray[i]);

		this.canvasDoubleBuff_1pixData.data[i * 4] = this
				.getInterpolateColorR(); // colors_R[colorIndex];
		this.canvasDoubleBuff_1pixData.data[i * 4 + 1] = this
				.getInterpolateColorG(); // colors_G[colorIndex];
		this.canvasDoubleBuff_1pixData.data[i * 4 + 2] = this
				.getInterpolateColorB(); // colors_B[colorIndex];

		this.canvasDoubleBuff_1pixData.data[i * 4 + 3] = 0xff; // opaque
	}

	this.canvasDoubleBuffer2Dcontext.putImageData(
			this.canvasDoubleBuff_1pixData, this.canWidth - 1, 0);

	document.getElementById('echoCanvas').getContext('2d').drawImage(
			this.canvasDoubleBuffElement, 0, 0);
}

/**
 * Use this after the new data has been received
 */
EchoCanvas.prototype.setNewData = function(data) {
	this.colorArray = data;
}

/**
 * E.g. colorStartIndex = 3 and colorRest = 0,2 => interpolate as
 * colorArray[3]*0.8 + colorArray[4]*0.2;
 */
EchoCanvas.prototype.interpolateColorIndex = function(rgb) {

	this.colorStartIndex = parseInt((rgb * (noOfColors - 1)) / 255);
	this.colorRest = ((rgb * (noOfColors - 1)) / 255) - this.colorStartIndex;
}

EchoCanvas.prototype.getInterpolateColorR = function() {
	return parseInt(colors_R[this.colorStartIndex] * (1 - this.colorRest)
			+ colors_R[this.colorStartIndex + 1] * this.colorRest);
}

EchoCanvas.prototype.getInterpolateColorG = function() {
	return parseInt(colors_G[this.colorStartIndex] * (1 - this.colorRest)
			+ colors_G[this.colorStartIndex + 1] * this.colorRest);
}

EchoCanvas.prototype.getInterpolateColorB = function() {
	return parseInt(colors_B[this.colorStartIndex] * (1 - this.colorRest)
			+ colors_B[this.colorStartIndex + 1] * this.colorRest);
}
