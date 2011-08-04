var noOfColors = 19; // !!! set this number to length of your color array

// DON'T REMOVE. This is array for green color

var colors_R2 = new Array(0x00, 0x00, 0x09, 0x0D, 0x1C, 0x49, 0x58, 0x8C, 0xBC, 0xDC); 
var colors_G2 = new Array(0x00, 0x45, 0x60, 0x8E, 0x9D, 0xAF, 0xBF, 0xCF, 0xFF, 0xFF); 
var colors_B2 = new Array(0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x22, 0x53, 0x80, 0xC3);

var colors_R3 = new Array(0x00, 15, 30, 45, 60, 85,   90,  105,  120,  135); 
var colors_G3 = new Array(0x00, 24, 52, 88, 112, 138, 162, 188, 214, 240); 
var colors_B3 = new Array(0x00, 28, 56, 94, 122, 150, 178, 206, 234, 255);
/*
var colors_R3 = new Array(0x00, 10, 20, 30, 40, 50,   60,  70,  80,  90); 
var colors_G3 = new Array(0x00, 20, 40, 60, 80, 100, 120, 140, 160, 180); 
var colors_B3 = new Array(0x00, 22, 44, 66, 88, 110, 132, 154, 176, 198);*/

/*var colors_R2 = new Array(0x00, 0x00, 0x09, 0x0D, 0x1C, 0x49, 0x58, 0x8C,
 0xBC, 0xDC); 
var colors_G2 = new Array(0x00, 0x25, 0x40, 0x5E, 0x6D, 0x9D,
0xBE, 0xFF, 0xFF, 0xFF); 
var colors_B2 = new Array(0x00, 0x00, 0x09, 0x0D,
0x1C, 0x29, 0x38, 0x5C, 0x8C, 0xAC);*/


var colors_R = new Array(40, 80, 40, 0, 0, 0, 0, 0, 40, 120, 200, 240, 252,
		224, 180, 160, 120, 80, 40);
var colors_G = new Array(252, 220, 140, 80, 40, 0, 80, 120, 160, 200, 200, 240,
		200, 120, 80, 0, 0, 0, 0);
var colors_B = new Array(252, 220, 192, 168, 160, 128, 64, 40, 0, 0, 0, 0, 0,
		0, 0, 20, 40, 20, 0);


function changeToGreen() {
	colors_R = colors_R3;
	colors_G = colors_G3;
	colors_B = colors_B3;
	noOfColors = 10;
}
// //////////////////////////////
// EchoCanvas class
function EchoCanvas(x, y, canWidth, canHeight) {
	this.x = x;
	this.y = y;
	this.test = 1;
	this.canWidth = canWidth;
	this.canHeight = canHeight;
	this.canvasDoubleBuffElement = null;
	this.canvasDoubleBuffer2Dcontext = null;
	this.canvasDoubleBuff_1pixData = null;

	this.colorArray = new Array(); // received data

	this.colorStartIndex;
	this.colorRest;

	this.echoPainter_init();
} // end of class

EchoCanvas.prototype.resize = function(x, y, canWidth, canHeight) {
	this.x = x;
	this.y = y;
	this.canWidth = canWidth;
	this.canHeight = canHeight;
}

// public methode, class EchoCanvas
EchoCanvas.prototype.echoPainter_init = function() {

	this.canvasDoubleBuffElement = document.createElement('canvas');
	this.canvasDoubleBuffElement.width = this.canWidth;// + 20; // 20 pix if
	// painting 20
	// times in one
	// sec.(sleep
	// 50ms)
	this.canvasDoubleBuffElement.height = this.canHeight;

	this.canvasDoubleBuffer2Dcontext = this.canvasDoubleBuffElement
			.getContext('2d');
	
	this.canvasDoubleBuffer2Dcontext.fillStyle = "#000"; 
	this.canvasDoubleBuffer2Dcontext.fillRect(0,0,this.canWidth,this.canHeight); 

	this.canvasDoubleBuff_1pixData = this.canvasDoubleBuffer2Dcontext
			.createImageData(1, this.canHeight);
}

EchoCanvas.prototype.paintChangedRange = function(oldRange) {
	range_PaintChangedRange(oldRange, this.canvasDoubleBuffer2Dcontext, this.canWidth - 4);
	//this.canvasDoubleBuffElement
	//.getContext('2d')
	
}

/**
 * public method, class EchoCanvas
 */
EchoCanvas.prototype.echoPainter_PaintCanvas = function() {
	// copy the same buffer one pixel left
	this.canvasDoubleBuffer2Dcontext.drawImage(this.canvasDoubleBuffElement,
			-1, 0);
	// TODO: if "createImageData" is not supported by browser, use:
	// "getImageData" (IE9?)
	// var imageData = canvasDoubleBuffer2Dcontext.createImageData(1,
	// nCanasHeight);

	if (this.colorArray != null) {
		for ( var i = 0; i < 400; i++) {
			this.interpolateColorIndex(this.colorArray[i]); //399 - i]);

			this.canvasDoubleBuff_1pixData.data[i * 4] = this
					.getInterpolateColorR(); // colors_R[colorIndex];
			this.canvasDoubleBuff_1pixData.data[i * 4 + 1] = this
					.getInterpolateColorG(); // colors_G[colorIndex];
			this.canvasDoubleBuff_1pixData.data[i * 4 + 2] = this
					.getInterpolateColorB(); // colors_B[colorIndex];

			this.canvasDoubleBuff_1pixData.data[i * 4 + 3] = 0xff; // opaque
		}

		this.canvasDoubleBuffer2Dcontext.putImageData(
				this.canvasDoubleBuff_1pixData, this.canWidth - 1, this.y);

		document.getElementById('echoCanvas').getContext('2d').drawImage(
				this.canvasDoubleBuffElement, this.x, this.y);//, this.canWidth,
				//this.canHeight);
		/*document.getElementById('echoCanvas').getContext('2d').font = "bold 36px sans-serif";
		document.getElementById('echoCanvas').getContext('2d').fillText(
				"" + this.test, 10, 30);*/
		this.test++;
	} else {
		//TODO: if data has not been received
	}
}

/**
 * Use this after the new data has been received
 */
EchoCanvas.prototype.setNewData = function(data) {
	for (i = 0; i < 400; i++)
	this.colorArray[i] = data[i+1]; //TODO: not "elegant". First element is depth
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
	if (this.colorStartIndex < (noOfColors - 1))
		return parseInt(colors_R[this.colorStartIndex] * (1 - this.colorRest)
			+ colors_R[this.colorStartIndex + 1] * this.colorRest);
	else
		return colors_R[this.colorStartIndex];
}

EchoCanvas.prototype.getInterpolateColorG = function() {
	if (this.colorStartIndex < (noOfColors - 1))
	return parseInt(colors_G[this.colorStartIndex] * (1 - this.colorRest)
			+ colors_G[this.colorStartIndex + 1] * this.colorRest);
	else
		return colors_G[this.colorStartIndex];
}

EchoCanvas.prototype.getInterpolateColorB = function() {
	if (this.colorStartIndex < (noOfColors - 1))
	return parseInt(colors_B[this.colorStartIndex] * (1 - this.colorRest)
			+ colors_B[this.colorStartIndex + 1] * this.colorRest);
	else
		return colors_B[this.colorStartIndex];
}
