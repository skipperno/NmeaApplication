
function getTimeScaleStorage(){
	var timeScale = window.localStorage.getItem('timeSc');
	if (timeScale == null) {
		timeScale = 2;
		setTimeScaleStorage(timeScale);
	}
	return timeScale;
}

function setTimeScaleStorage(newTimeScale){
	 window.localStorage.setItem('timeSc', newTimeScale);
}

function getDepthTypeStorage(){
	var dp = window.localStorage.getItem('depthTy');
	if (dp == null || dp < 0 || dp > 2) {
		dp = 0;
		setDepthTypeStorage(dp);
	}
	return dp;
}

function setDepthTypeStorage(newDP){
	 window.localStorage.setItem('depthTy', newDP);
}