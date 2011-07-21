var segmentHeight=60;

/*
SliderVertical.isSupported = typeof document.createElement != "undefined" &&
	typeof document.documentElement != "undefined" &&
	typeof document.documentElement.offsetWidth == "number";*/
	
function onVerticalSliderMoved(sliderIndex, pos) {
	/*if (sliderIndex == 3) {
		changeTimeRange(pos);
	} else if (sliderIndex == 4) {
		changeRange(pos);
	}*/
}


function SliderVertical(slidIndex, slMin, slMax, slStart, parentContainer,textArray) {
	this.currentStep=0;
	this.mouseDownX;
	this.mouseDownY;
	this.sliderIndex = slidIndex;
	this.slMin = slMin;
	this.slMax = slMax;
	this.slStart = slStart;
	this.myId = slidIndex;
	this.parentContainer = parentContainer;
	
	this.document = parentContainer.ownerDocument || parentContainer.document;
	
	
	this.verticalSliderConteiner = this.document.createElement("DIV");
	this.verticalSliderConteiner.className = "verticalSliderConteiner";
	this.verticalSliderConteiner.unselectable = "on";
	/*
	this.mySlidImg = this.document.createElement("img");
	this.mySlidImg.setAttribute('src', imgUrl);
	this.mySlidImg.setAttribute('alt', 'alternate text');
	this.mySlidImg.setAttribute('width', '50px');
	this.mySlidImg.setAttribute('height', '80px');
	this.mySlidImg.setAttribute('margin-right', '20px');
	//this.mySlidImg.setAttribute('width', '100px');
*/
	this.verticalSliderBody = this.document.createElement("DIV");
	
	this.verticalSliderBody.className = "verticalSliderBody";
	this.verticalSliderBody.id = "verticalSliderBodyId_" + this.myId;
	this.verticalSliderBody.unselectable = "on";
	this.verticalSliderBody.myObject = this;
	//this.verticalSliderBody.style.background='#bbe';
	
	this.sliderTopButton = this.document.createElement("DIV");
	this.sliderTopButton.className = "sliderTopButton";
	this.sliderTopButton.myObject = this;
	
		
	this.sliderDownButton = this.document.createElement("DIV");
	this.sliderDownButton.className = "sliderDownButton";
	this.sliderDownButton.myObject = this;
	
	this.verticalSliderCenter = this.document.createElement("DIV");
	this.verticalSliderCenter.className = "verticalSliderCenter";
	this.verticalSliderCenter.myObject = this;
	
		this.verticalSliderHandleButton = this.document.createElement("DIV");
		this.verticalSliderHandleButton.className = "verticalSliderHandleButton";
		this.verticalSliderHandleButton.id = "verticalSliderHandleButtonId_" + this.myId;
		this.verticalSliderHandleButton.myObject = this;
		this.verticalSliderHandleButton.unselectable = "on";
			
		for (i=0;i<6;i++){
			this.verticalTextDiv = this.document.createElement("DIV");
			this.verticalTextDiv.className = "verticalTextDiv";
			this.verticalTextDiv.unselectable = "on";
			this.verticalTextDiv.innerHTML = textArray[i];
			this.verticalTextDiv.style.top= i*segmentHeight-6 + "px"; 
			this.verticalSliderCenter.appendChild(this.verticalTextDiv);
			
			this.verticalTextDiv2 = this.document.createElement("DIV");
			this.verticalTextDiv2.className = "verticalTextDiv2";
			this.verticalTextDiv2.unselectable = "on";
			this.verticalTextDiv2.innerHTML = textArray[i];
			this.verticalTextDiv2.style.top= i*segmentHeight-5 + "px"; 
			this.verticalSliderCenter.appendChild(this.verticalTextDiv2);
		}
		
		this.verticalSliderCenter.appendChild(this.verticalSliderHandleButton);
		
		this.verticalSliderBody.appendChild(this.sliderTopButton);
		this.verticalSliderBody.appendChild(this.verticalSliderCenter);
		this.verticalSliderBody.appendChild(this.sliderDownButton);
		

		//this.verticalSliderConteiner.appendChild(this.verticalSliderBody);
		
		this.parentContainer.appendChild(this.verticalSliderBody);//this.verticalSliderConteiner);
		
		
		
		this.setNewPos(slStart);

	//this.verticalSliderHandleButton.onmouseover	= MySliding.eventHandlers.onmouseover;
	//this.verticalSliderHandleButton.onmouseout		= MySliding.eventHandlers.onmouseout;
	//this.verticalSliderHandleButton.onmousedown		= MySliding.eventHandlers.onmousedown;

	$(this.sliderTopButton).mousedown(function(e){
		if(this.myObject.currentStep > 0)
			this.myObject.setNewPos((this.myObject.currentStep - 1)*segmentHeight, true);
	});
	
	$(this.sliderDownButton).mousedown(function(e){
		if(this.myObject.currentStep < 5)
			this.myObject.setNewPos((this.myObject.currentStep + 1)*segmentHeight, true);
	});

	$(this.verticalSliderCenter).mousedown(function(e){
		var offset = $(this).offset();
		//var offset = $(this).offset();
  		var x = parseInt(e.pageX - offset.left);
 		var y = parseInt(e.pageY - offset.top);

	 	/*this.myObject.mouseDownX = x;//mouseX; mousePos.
 		this.myObject.mouseDownY = y; // mouseY; mousePos.
		*/
		this.myObject.setNewPos(y, true);
	});

	$(this.verticalSliderHandleButton).mousedown(function(e){
		var offset = $(this).offset();
  		var x = parseInt(e.pageX - offset.left);
 		var y = parseInt(e.pageY - offset.top);

	 	this.myObject.mouseDownX = x;//mouseX; mousePos.
 		this.myObject.mouseDownY = y; // mouseY; mousePos.
		
		$(this.myObject.verticalSliderBody).mousemove(function(e){
			var offset2 = $(this).offset();
 			 var xx = parseInt(e.pageX - offset2.left);
  			var yy = parseInt(e.pageY - offset2.top);
			//alert("offY: " + parseInt(offset2.top) + " page: " + parseInt(e.pageY) +  " y= " + yy);
			//this.myObject.verticalSliderHandleButton.setAttribute("style", "left:" + (xx - this.myObject.mouseDownY) + "px");
			this.myObject.setNewPos(yy - this.myObject.mouseDownY, false);
			
			onVerticalSliderMoved(this.myObject.sliderIndex, (yy - this.myObject.mouseDownY));
			return preventEv(e);
		 });
		
		$(this.myObject.verticalSliderBody).mouseup(function(e){
			$(this).unbind('mousemove mouseup mouseout');
			var offset2 = $(this).offset();
 			 var xx = parseInt(e.pageX - offset2.left);
  			var yy = parseInt(e.pageY - offset2.top);
			
			this.myObject.setNewPos(yy - this.myObject.mouseDownY, true);
			return preventEv(e);
		 });

		return preventEv(e);
    }); 
}

SliderVertical.prototype.showSlider = function(show) {
	if (show)
		$(this.verticalSliderBody).show();
	else
		$(this.verticalSliderBody).hide();
}

SliderVertical.prototype.setNewPos = function(newX, anim) {
	this.currentStep = parseInt(newX/segmentHeight + 0.5);
	var calcX = this.currentStep*segmentHeight -5;
	
	if (anim){
		var strNewX="" + calcX;
		$(this.verticalSliderHandleButton).animate({top:strNewX},200);
	} else{
		this.verticalSliderHandleButton.setAttribute("style", "top:" + calcX + "px");
	}
}

function preventEv(e){
		if (e.preventDefault)
        		e.preventDefault();
    	else
        		e.returnValue= false;
    	return false;
	}
	


