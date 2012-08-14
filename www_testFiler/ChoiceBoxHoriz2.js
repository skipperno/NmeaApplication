


function ChoiceBoxHoriz2(choiceIndex, shownText, selectedIndex, parentContainer, choiceCount, choiceNamesArray, iconNorm, iconSelect, iconWidth, iconHeight, totWidth, totHeight, callbackFunc) {
	this.selectedIndex = selectedIndex;
	this.mouseDownX;
	this.mouseDownY;
	this.myId = choiceIndex;
	this.parentContainer = parentContainer;
	this.stepWidth;
	this.choiceCount = choiceCount; 
	this.choiceNamesArray = choiceNamesArray; 
	this.choicePosCenterArray = new Array();
	this.iconNorm = iconNorm;
	this.iconSelect = iconSelect;
	this.iconWidth = iconWidth;
	this.iconHeight = iconHeight;
	this.totWidth = totWidth;
	this.totHeight = totHeight;
	this.callbackFunc = callbackFunc;
	
	this.document = parentContainer.ownerDocument || parentContainer.document;

	this.horisChoiceCenter = this.document.createElement("DIV");
	this.horisChoiceCenter.className = "horisChoiceCenter";
	this.horisChoiceCenter.myObject = this;
	this.horisChoiceCenter.style.width = this.totWidth + "px";
	this.horisChoiceCenter.style.height = this.totHeight + "px";

	this.nameDiv = this.document.createElement("DIV");
	this.nameDiv.id = "horChoiceMainText";
	this.nameDiv.innerHTML = shownText;
	//this.nameDiv.style.left = "150px";
	this.nameDiv.style.top = (iconHeight + 5)+ "px";
	
	this.horisChoiceCenter.appendChild(this.nameDiv);
	
	this.horChoiceSelectedIcon = this.document.createElement("DIV");
	this.horChoiceSelectedIcon.className = "horChoiceSelectedIcon";
	this.horChoiceSelectedIcon.id = "horChoiceSelectedIconId_" + this.myId;
	this.horChoiceSelectedIcon.myObject = this;
	this.horChoiceSelectedIcon.unselectable = "on";
	
	this.calcChoisePos();
	
	for (i = 0; i < choiceCount; i++) {
		this.txtDiv = this.document.createElement("DIV");
		this.txtDiv.className = "horChoiceText";
		this.txtDiv.innerHTML = this.choiceNamesArray[i];
		this.txtDiv.style.left = this.choicePosCenterArray[i] - 50 + "px";
		this.txtDiv.style.top = this.iconHeight/2 - 7 + "px";
		
		
		
		this.horChoiceIcon = this.document.createElement("DIV");
		this.horChoiceIcon.className = "choiceIc";
		this.horChoiceIcon.id = "choiceIc_id_" + this.myId + "_" + i;		
		this.horChoiceIcon.style.backgroundImage="url(images/" + this.iconNorm + ")";
		this.horChoiceIcon.style.width = this.iconWidth + "px";
		this.horChoiceIcon.style.height = this.iconHeight+ "px";
		this.horChoiceIcon.style.left = this.choicePosCenterArray[i] - this.iconWidth/2 + "px";
		
		this.horisChoiceCenter.appendChild(this.horChoiceIcon);
		this.horisChoiceCenter.appendChild(this.txtDiv);
	}

//	this.horisSlider.appendChild(this.leftButt);
//	this.horisChoice.appendChild(this.horisChoiceCenter);
//	this.horisSlider.appendChild(this.rightButt);
	

	this.parentContainer.appendChild(this.horisChoiceCenter);// this.mySlidConteiner);
	
	this.selectChoice(this.selectedIndex);

	$(this.horisChoiceCenter).click(function(e) {//mousedown(function(e) {
		
		var offset = $(this).offset();
		var x = parseInt(e.pageX - offset.left);
		var y = parseInt(e.pageY - offset.top);
		if (y > this.myObject.iconHeight)
			return preventEv(e);
		
		var newSelectedIndex = this.myObject.convertPosToValue(x);

		this.myObject.selectChoice(newSelectedIndex);
		
		if (this.myObject.callbackFunc != null)
			this.myObject.callbackFunc(this.myObject.myId, newSelectedIndex);
		else
			onSliderMoved(this.myObject.myId, newSelectedIndex);
		
		return preventEv(e);
	});
}

ChoiceBoxHoriz2.prototype.showChoice = function(show) {
	if (show)
		$(this.horisChoice).show();
	else
		$(this.horisChoice).hide();
};

ChoiceBoxHoriz2.prototype.convertPosToValue = function(newX) {
	return parseInt(newX / this.step / 2);
};

ChoiceBoxHoriz2.prototype.calcChoisePos = function() {
	this.step = this.totWidth / this.choiceCount/2;
	for (i = 0; i < this.choiceCount; i++) {
		this.choicePosCenterArray[i] = parseInt(this.step*i*2 + this.step);
	}
};


ChoiceBoxHoriz2.prototype.selectChoice = function(selIndex) {
	var myElem = document.getElementById("choiceIc_id_" + this.myId + "_" + this.selectedIndex);
	if (myElem != null)
		myElem.style.backgroundImage="url(images/" + this.iconNorm + ")";
	
	myElem = document.getElementById("choiceIc_id_" + this.myId + "_" + selIndex);
	myElem.style.backgroundImage="url(images/" + this.iconSelect + ")";
	
	this.selectedIndex = selIndex;
};
/*
function preventEv(e) {
	if (e.preventDefault)
		e.preventDefault();
	else
		e.returnValue = false;
	return false;
}*/
