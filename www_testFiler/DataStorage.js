var DEFAULT_TIME_SCALE = 5; //50 sec /route
var DEFAULT_DEPTH_UNIT = 0; //[m]
var DEFAULT_DEPTH_TYPE = 0; //DPT
var DEFAULT_DEP_FONT = 1;
var DEFAULT_COLOR = 2;
var DEFAULT_VIEWING_DIST = 1; 
var DEFAULT_SCREEN_SIZE = 0; // 8''



function getTimeScaleStorage(){
	if (!window.localStorage)
		return DEFAULT_TIME_SCALE;
	
	var timeScale = window.localStorage.getItem('timeSc');
	if (timeScale == null) {
		timeScale = DEFAULT_TIME_SCALE;
		setTimeScaleStorage(timeScale);
	}
	return timeScale;
}

function setTimeScaleStorage(newTimeScale){
	if (!window.localStorage)
		return;
	 window.localStorage.setItem('timeSc', newTimeScale);
}


function getDepthTypeStorage(){
	if (!window.localStorage)
		return DEFAULT_DEPTH_TYPE;
	var dp = window.localStorage.getItem('depthTy');
	if (dp == null || dp < 0 || dp > 2) {
		dp = DEFAULT_DEPTH_TYPE;
		setDepthTypeStorage(dp);
	}
	return dp;
}

function setDepthTypeStorage(newDP){
	if (!window.localStorage)
		return;
	 window.localStorage.setItem('depthTy', newDP);
}

function getDepthUnitStorage(){
	if (!window.localStorage)
		return DEFAULT_DEPTH_UNIT;
	var temp = window.localStorage.getItem('depthUn');
	if (temp == null) {
		temp = DEFAULT_DEPTH_UNIT;
		setDepthUnitStorage(temp);
	}
	
	return temp;
}

function setDepthUnitStorage(newDepthUnit){
	if (!window.localStorage)
		return;
	
	 window.localStorage.setItem('depthUn', newDepthUnit);
	 currDepthUnit = newDepthUnit;
}

function getDepthFontStorage(){
	if (!window.localStorage)
		return DEFAULT_DEP_FONT; 
	var temp = window.localStorage.getItem('depF');
	if (temp == null) {
		temp = DEFAULT_DEP_FONT;
		setDepthFontStorage(temp);
	}
	return temp;
}

function setDepthFontStorage(newValue){
	if (!window.localStorage)
		return;
	
	 window.localStorage.setItem('depF', newValue);
}

function getColorStorage(){
	if (!window.localStorage)
		return DEFAULT_COLOR;
	var temp = window.localStorage.getItem('col');
	if (temp == null) {
		temp = DEFAULT_COLOR;
		setColorStorage(temp);
	}
	return temp;
}

function setColorStorage(newValue){
	if (!window.localStorage)
		return;
	 window.localStorage.setItem('col', newValue);
}

///////////  VIEWING DISTANCE  ////////////////////
function getViewingDistanceStorage(){
	if (!window.localStorage)
		return DEFAULT_VIEWING_DIST;
	var temp = window.localStorage.getItem('vd');
	if (temp == null) {
		temp = DEFAULT_VIEWING_DIST;
		setViewingDistanceStorage(temp);
	}
	return temp;
}

function setViewingDistanceStorage(newValue){
	if (!window.localStorage)
		return;
	 window.localStorage.setItem('vd', newValue);
}

///////////  SCREEN SIZE  ////////////////////
function getScreenSizeStorage(){
	if (!window.localStorage)
		return DEFAULT_SCREEN_SIZE;
	var temp = window.localStorage.getItem('ss');
	if (temp == null) {
		temp = DEFAULT_SCREEN_SIZE;
		setScreenSizeStorage(temp);
	}
	return temp;
}

function setScreenSizeStorage(newValue){
	if (!window.localStorage)
		return;
	 window.localStorage.setItem('ss', newValue);
}


