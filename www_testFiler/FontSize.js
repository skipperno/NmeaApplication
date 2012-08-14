var distArray=[1, 2, 3, 5];

var maxPixFont = 170; // [px]

// Screen 640x800, 8.4 inch => 1px = 0,27mm
//Screen 640x800, 10,4 inch => 1px = 0,34mm
var screenFactor=[0.2, 0.25];

function recalculateFontSize(){
	var distIndex = getViewingDistanceStorage();
	var minFont = distArray[distIndex]*3.5; //[mm]
	var minPixFont = parseInt(minFont/screenFactor[getScreenSizeStorage()] + 0.5);
	if (minPixFont < 8)
		minPixFont = 8;
	
	// "depthFontSizeArr" is defined in "DepthInfo.js"
	depthFontSizeArr[0] = minPixFont;
	depthFontSizeArr[1] = minPixFont + (maxPixFont - minPixFont)/3;
	depthFontSizeArr[2] = minPixFont + (maxPixFont - minPixFont)*2/3;
	depthFontSizeArr[3] = maxPixFont;
	
}
