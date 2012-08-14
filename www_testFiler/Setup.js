function updateSetupScreenValues() {
	setCheckedValue("depTyp",getDepthTypeStorage());
	setCheckedValue("depUn",getDepthUnitStorage());
	setCheckedValue("depF",getDepthFontStorage());
}


function setCheckedValue(radioObjName, newIndex) {
	var radioObj = document.getElementsByName(radioObjName);
	if(!radioObj)
		return;
	
	for(var i = 0; i < radioObj.length; i++) {
		radioObj[i].checked = false;
		if(i == newIndex) {
			radioObj[i].checked = true;
		}
	}
}