
var CHOICE_SELECT_IMAGE_WIDTH = 32;


function ChoiceBoxHoriz(choiceIndex, shownText, selectedIndex, parentContainer, choiceCount, choiceNamesArray) {
	this.selectedIndex = selectedIndex;
	this.mouseDownX;
	this.mouseDownY;
	this.selectedIndex = selectedIndex;
	this.myId = choiceIndex;
	this.parentContainer = parentContainer;
	this.stepWidth;
	this.choiceCount = choiceCount; 
	this.choiceNamesArray = choiceNamesArray; 
	this.choicePosCenterArray = new Array();
	
	this.document = parentContainer.ownerDocument || parentContainer.document;

	this.horisChoice = this.document.createElement("DIV");

	this.horisChoice.className = "horisChoice";
	this.horisChoice.id = "horisChoiceId_" + this.myId;
	this.horisChoice.unselectable = "on";
	this.horisChoice.myObject = this;
	// this.horisSlider.style.background='#bbe';

	this.horisChoiceCenter = this.document.createElement("DIV");
	this.horisChoiceCenter.className = "horisChoiceCenter";
	this.horisChoiceCenter.myObject = this;

	this.nameDiv = this.document.createElement("DIV");
	this.nameDiv.className = "horChoiceText";
	this.nameDiv.unselectable = "on";
	this.nameDiv.innerHTML = shownText;
	this.nameDiv.style.left = "150px";
	this.nameDiv.style.top = "45px";
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
		this.txtDiv.unselectable = "on";
		this.txtDiv.innerHTML = this.choiceNamesArray[i];
		this.txtDiv.style.left = this.choicePosCenterArray[i] - 50 + "px";
		this.horisChoiceCenter.appendChild(this.txtDiv);
		
		this.horChoiceIcon = this.document.createElement("DIV");
		this.horChoiceIcon.className = "horChoiceIcon";
		this.horChoiceIcon.unselectable = "on";
		this.horChoiceIcon.style.left = this.choicePosCenterArray[i] - CHOICE_SELECT_IMAGE_WIDTH/2 + "px";
		this.horisChoiceCenter.appendChild(this.horChoiceIcon);
	}

//	this.horisSlider.appendChild(this.leftButt);
	this.horisChoice.appendChild(this.horisChoiceCenter);
//	this.horisSlider.appendChild(this.rightButt);
	this.horisChoice.appendChild(this.horChoiceSelectedIcon);

	this.parentContainer.appendChild(this.horisChoice);// this.mySlidConteiner);
	
	this.selectChoice(this.selectedIndex,false);

	$(this.horisChoiceCenter).mouseup(function(e) {
		var offset = $(this).offset();
		var x = parseInt(e.pageX - offset.left);
		var y = parseInt(e.pageY - offset.top);
		
		this.myObject.selectedIndex = this.myObject.convertPosToValue(x);
		
		this.myObject.selectChoice(this.myObject.selectedIndex, true);
		
		onSliderMoved(this.myObject.myId, this.myObject.selectedIndex);
		return preventEv(e);
	});
}

ChoiceBoxHoriz.prototype.showChoice = function(show) {
	if (show)
		$(this.horisChoice).show();
	else
		$(this.horisChoice).hide();
}

ChoiceBoxHoriz.prototype.convertPosToValue = function(newX) {
	return parseInt(newX / this.step / 2);
}

ChoiceBoxHoriz.prototype.calcChoisePos = function() {
	this.step = 400 / this.choiceCount/2;
	for (i = 0; i < this.choiceCount; i++) {
		this.choicePosCenterArray[i] = parseInt(this.step*i*2 + this.step);
	}
}


ChoiceBoxHoriz.prototype.selectChoice = function(selIndex, anim) {
	calcX = this.step*selIndex*2 + this.step - CHOICE_SELECT_IMAGE_WIDTH/2;
	
	if (anim) {
		var strNewX = "" + calcX;
		$(this.horChoiceSelectedIcon).animate({
			left : strNewX
		}, 200);
	} else {
		this.horChoiceSelectedIcon.setAttribute("style", "left:" + calcX + "px");
	}
}

function preventEv(e) {
	if (e.preventDefault)
		e.preventDefault();
	else
		e.returnValue = false;
	return false;
}
