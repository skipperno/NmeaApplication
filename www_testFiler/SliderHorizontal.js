var HANDL_BUTTON_IMAGE_WIDTH = 12;

SliderHorizontal.isSupported = typeof document.createElement != "undefined"
		&& typeof document.documentElement != "undefined"
		&& typeof document.documentElement.offsetWidth == "number";

function SliderHorizontal(slidIndex, slidName, slMin, slMax, slStart,
		parentContainer, textArray, bDiscret) {
	this.currentValue = slStart;
	this.currentPos = 0;
	this.mouseDownX;
	this.mouseDownY;
	this.sliderIndex = slidIndex;
	this.slMin = slMin;
	this.slMax = slMax;
	this.myId = slidIndex;
	this.parentContainer = parentContainer;
	this.stepWidth;
	this.bDiscret = bDiscret;
	this.segmentCount = 5; // 0-20, 20-40, 40-60, 60-80, 80-100

	this.document = parentContainer.ownerDocument || parentContainer.document;

	this.mySlidConteiner = this.document.createElement("DIV");
	this.mySlidConteiner.className = "mySlidCont";
	this.mySlidConteiner.unselectable = "on";

	this.horisSlider = this.document.createElement("DIV");

	this.horisSlider.className = "horisSlid";
	this.horisSlider.id = "horisSlidId_" + this.myId;
	this.horisSlider.unselectable = "on";
	this.horisSlider.myObject = this;
	// this.horisSlider.style.background='#bbe';

	this.leftButt = this.document.createElement("DIV");
	this.leftButt.className = "horisSlidLeft";
	this.leftButt.myObject = this;

	this.rightButt = this.document.createElement("DIV");
	this.rightButt.className = "horisSlidRight";
	this.rightButt.myObject = this;

	this.slidCenter = this.document.createElement("DIV");
	this.slidCenter.className = "horisSlidCenter";
	this.slidCenter.myObject = this;

	if (this.bDiscret) {
		// this.stepWidth = 60; // 60px for ++ or --
		this.stepValueJump = (slMax - slMin) / this.segmentCount; // e.g. 20
																	// if values
																	// are: 0,
																	// 20, 40,
																	// ...
	} else {
		// this.stepWidth = 300 / (slMax - slMin); // slider center div is 300px
		this.stepValueJump = 1;
	}

	this.nameDiv = this.document.createElement("DIV");
	this.nameDiv.className = "horisSlidName";
	this.nameDiv.unselectable = "on";
	this.nameDiv.innerHTML = slidName;
	this.nameDiv.style.left = "75px";
	this.nameDiv.style.top = "45px";
	this.slidCenter.appendChild(this.nameDiv);

	this.myHandlBut = this.document.createElement("DIV");
	this.myHandlBut.className = "horisSlidHandlBut";
	this.myHandlBut.id = "myHandlButId_" + this.myId;
	this.myHandlBut.myObject = this;
	this.myHandlBut.unselectable = "on";

	for (i = 0; i < 6; i++) {
		this.txtDiv = this.document.createElement("DIV");
		this.txtDiv.className = "horisSlidText";
		this.txtDiv.unselectable = "on";
		this.txtDiv.innerHTML = textArray[i];
		this.txtDiv.style.left = i * 60 - 28 + "px";
		this.slidCenter.appendChild(this.txtDiv);
	}

	this.slidCenter.appendChild(this.myHandlBut);

	this.horisSlider.appendChild(this.leftButt);
	this.horisSlider.appendChild(this.slidCenter);
	this.horisSlider.appendChild(this.rightButt);

	this.parentContainer.appendChild(this.horisSlider);// this.mySlidConteiner);
	this.setHandlButtPos(parseInt(slStart * 300 / (this.slMax - this.slMin)),
			false);

	$(this.leftButt)
			.mousedown(
					function(e) {
						if (this.myObject.currentValue > this.myObject.slMin) {
							this.myObject.currentValue -= this.myObject.stepValueJump;
							this.myObject
									.setHandlButtPos(
											parseInt((this.myObject.currentValue - this.myObject.slMin)
													* 300
													/ (this.myObject.slMax - this.myObject.slMin)),
											false);

							onSliderMoved(this.myObject.sliderIndex,
									this.myObject.currentValue);
						}
						return preventEv(e);
					});

	$(this.rightButt)
			.mousedown(
					function(e) {
						if (this.myObject.currentValue < this.myObject.slMax) {
							this.myObject.currentValue += this.myObject.stepValueJump;
							this.myObject
									.setHandlButtPos(
											(this.myObject.currentValue - this.myObject.slMin)
													* 300
													/ (this.myObject.slMax - this.myObject.slMin),
											true);

							onSliderMoved(this.myObject.sliderIndex,
									this.myObject.currentValue);
						}
						return preventEv(e);
					});


	$(this.slidCenter).mouseup (
					function(e) {
						if (!buttonPushed) {
							var offset = $(this).offset();
							var x = parseInt(e.pageX - offset.left);
							var y = parseInt(e.pageY - offset.top);

							if (!this.myObject.bDiscret) {
								this.myObject.setHandlButtPos(x, true);
							} else if (this.myObject.bDiscret) {
								var pixelStep = 300 / ((this.slMax - this.slMin) / this.myObject.stepValueJump);
								x += pixelStep / 2;
								var discrX = parseInt(x / pixelStep)
										* pixelStep;
								this.myObject.setHandlButtPos(discrX);
							}

							this.myObject.currentValue = this.myObject
									.convertPosToValue();

							onSliderMoved(this.myObject.sliderIndex,
									this.myObject.currentValue);
						} else {
							buttonPushed = false;
							$(this.myObject.slidCenter).unbind('mousemove');
							var offset2 = $(this).offset();
							var xx = parseInt(e.pageX - offset2.left);
							var yy = parseInt(e.pageY - offset2.top);
							
							//!!!!!!!!!!!!!!
							this.myObject.setHandlButtPos(xx
									- this.myObject.mouseDownX, true);
							this.myObject.currentValue = this.myObject.convertPosToValue();
							onSliderMoved(this.myObject.sliderIndex, this.myObject.currentValue);
						}
						return preventEv(e);
					});
	
	$(this.slidCenter).mouseleave(
			function(e) {
				if (buttonPushed) {
					buttonPushed = false;
					$(this.myObject.slidCenter).unbind('mousemove');
					//$(this.myObject.slidCenter).unbind('mouseleave');
					var offset2 = $(this).offset();
					var xx = parseInt(e.pageX - offset2.left);
					var yy = parseInt(e.pageY - offset2.top);
					
					//!!!!!!!!!!!!!!
					this.myObject.setHandlButtPos(xx
							- this.myObject.mouseDownX, true);
					this.myObject.currentValue = this.myObject.convertPosToValue();
					onSliderMoved(this.myObject.sliderIndex, this.myObject.currentValue);
				}
				return preventEv(e);
			});

	var currSlider;
	var buttonPushed = false;
	$(this.myHandlBut).mousedown(
			function(e) {
				currSlider = this.myObject;
				buttonPushed = true;
				var offset = $(this).offset();
				var x = parseInt(e.pageX - offset.left);
				var y = parseInt(e.pageY - offset.top);

				this.myObject.mouseDownX = HANDL_BUTTON_IMAGE_WIDTH / 2 - x;// mouseX;
																			// mousePos.
				this.myObject.mouseDownY = y; // mouseY; mousePos.
				
				$(this.myObject.parentContainer).mouseup(
						function(e) {
							if(buttonPushed){
								buttonPushed = false;
								onSliderMoved(currSlider.sliderIndex, currSlider.currentValue);
								//$(this).unbind('mouseup');
							}
							return preventEv(e);
						});
						

				$(this.myObject.slidCenter).mousemove(
						function(e) {
							var offset2 = $(this).offset();
							var xx = parseInt(e.pageX - offset2.left);
							var yy = parseInt(e.pageY - offset2.top);
							//if(xx < 300 && xx >= 0){

								this.myObject.setHandlButtPos(xx
									- this.myObject.mouseDownX, false);
						/*	} else {
								$(this).unbind('mousemove');
								buttonPushed = false;
								if (xx >= 300)
									this.myObject.setHandlButtPos(299, false);
								else
									this.myObject.setHandlButtPos(0, false);
								this.myObject.currentValue = this.myObject.convertPosToValue();
								onSliderMoved(this.myObject.sliderIndex, this.myObject.currentValue);
							}*/
							return preventEv(e);
						});

				/*
				 * $(this.myObject.slidCenter).mouseout( function(e) {
				 * $(this).unbind('mousemove mouseup mouseout'); });
				 */

				return preventEv(e);
			});
}
SliderHorizontal.prototype.changeUnderText = function(newText) {
	this.nameDiv.innerHTML = newText;
};

SliderHorizontal.prototype.showSlider = function(show) {
	if (show)
		$(this.horisSlider).show();
	else
		$(this.horisSlider).hide();
};

SliderHorizontal.prototype.convertPosToValue = function() {
	return this.slMin
			+ parseInt(this.currentPos * (this.slMax - this.slMin) / 300);
};

SliderHorizontal.prototype.convertValToPosition = function(newValue) {
	return parseInt((newValue - this.slMin) * 300 / (this.slMax - this.slMin));
};

// !!! newX is pixel position. If you don't have, use "setHandButtValue"
SliderHorizontal.prototype.setHandlButtPos = function(newX, anim) {
	if(newX >= 300)
		newX = 300;
	else if (newX < 0) {
		newX = 0;
	}
	calcX = newX - HANDL_BUTTON_IMAGE_WIDTH / 2;
	this.currentPos = newX;
	if (anim) {
		var strNewX = "" + calcX;
		$(this.myHandlBut).animate({
			left : strNewX
		}, 200);
	} else {
		this.myHandlBut.setAttribute("style", "left:" + calcX + "px");
	}
};
// Not callback from this function.
SliderHorizontal.prototype.setHandlButtValue = function(newValue, anim) {
	this.setHandlButtPos(this.convertValToPosition(newValue));
	this.currentValue = newValue;
};
/*
 * SliderHorizontal.prototype.setHandlButtValue = function(newValue, anim) { var
 * newX = this.stepWidth*newValue; calcX = newX; // -
 * HANDL_BUTTON_IMAGE_WIDTH/2;
 * 
 * if (anim) { var strNewX = "" + calcX; $(this.myHandlBut).animate({ left :
 * strNewX }, 200); } else { this.myHandlBut.setAttribute("style", "left:" +
 * calcX + "px"); } };
 */

function preventEv(e) {
	if (e.preventDefault)
		e.preventDefault();
	else
		e.returnValue = false;
	return false;
}
