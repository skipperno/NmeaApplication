var segmentWidth=60;


SliderHorizontal.isSupported = typeof document.createElement != "undefined" &&
	typeof document.documentElement != "undefined" &&
	typeof document.documentElement.offsetWidth == "number";
	
function onSliderMoved(sliderIndex, pos) {
	/*if (sliderIndex == 3) {
		changeTimeRange(pos);
	} else if (sliderIndex == 4) {
		changeRange(pos);
	}*/
}


function SliderHorizontal(slidIndex, slMin, slMax, slStart, parentContainer,textArray) {
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
	
	
	this.mySlidConteiner = this.document.createElement("DIV");
	this.mySlidConteiner.className = "mySlidCont";
	this.mySlidConteiner.unselectable = "on";
	/*
	this.mySlidImg = this.document.createElement("img");
	this.mySlidImg.setAttribute('src', imgUrl);
	this.mySlidImg.setAttribute('alt', 'alternate text');
	this.mySlidImg.setAttribute('width', '50px');
	this.mySlidImg.setAttribute('height', '80px');
	this.mySlidImg.setAttribute('margin-right', '20px');
	//this.mySlidImg.setAttribute('width', '100px');
*/
	this.horisSlider = this.document.createElement("DIV");
	
	this.horisSlider.className = "horisSlid";
	this.horisSlider.id = "horisSlidId_" + this.myId;
	this.horisSlider.unselectable = "on";
	this.horisSlider.myObject = this;
	//this.horisSlider.style.background='#bbe';
	
	this.leftButt = this.document.createElement("DIV");
	this.leftButt.className = "horisSlidLeft";
	this.leftButt.myObject = this;
	
		
	this.rightButt = this.document.createElement("DIV");
	this.rightButt.className = "horisSlidRight";
	this.rightButt.myObject = this;
	
	this.slidCenter = this.document.createElement("DIV");
	this.slidCenter.className = "horisSlidCenter";
	this.slidCenter.myObject = this;
	
		this.myHandlBut = this.document.createElement("DIV");
		this.myHandlBut.className = "horisSlidHandlBut";
		this.myHandlBut.id = "myHandlButId_" + this.myId;
		this.myHandlBut.myObject = this;
		this.myHandlBut.unselectable = "on";
			
		for (i=0;i<6;i++){
			this.txtDiv = this.document.createElement("DIV");
			this.txtDiv.className = "horisSlidText";
			this.txtDiv.unselectable = "on";
			this.txtDiv.innerHTML = textArray[i];
			this.txtDiv.style.left= i*segmentWidth-28 + "px"; 
			this.slidCenter.appendChild(this.txtDiv);
		}
		
		this.slidCenter.appendChild(this.myHandlBut);
		
		this.horisSlider.appendChild(this.leftButt);
		this.horisSlider.appendChild(this.slidCenter);
		this.horisSlider.appendChild(this.rightButt);
		

		//this.mySlidConteiner.appendChild(this.horisSlider);
		
		this.parentContainer.appendChild(this.horisSlider);//this.mySlidConteiner);
		
		
		
		this.setNewPos(slStart);

	//this.myHandlBut.onmouseover	= MySliding.eventHandlers.onmouseover;
	//this.myHandlBut.onmouseout		= MySliding.eventHandlers.onmouseout;
	//this.myHandlBut.onmousedown		= MySliding.eventHandlers.onmousedown;

	$(this.leftButt).mousedown(function(e){
		if(this.myObject.currentStep > 0)
			this.myObject.setNewPos((this.myObject.currentStep - 1)*segmentWidth, true);
	});
	
	$(this.rightButt).mousedown(function(e){
		if(this.myObject.currentStep < 5)
			this.myObject.setNewPos((this.myObject.currentStep + 1)*segmentWidth, true);
	});

	$(this.slidCenter).mousedown(function(e){
		var offset = $(this).offset();
		//var offset = $(this).offset();
  		var x = parseInt(e.pageX - offset.left);
 		var y = parseInt(e.pageY - offset.top);

	 	/*this.myObject.mouseDownX = x;//mouseX; mousePos.
 		this.myObject.mouseDownY = y; // mouseY; mousePos.
		*/
		this.myObject.setNewPos(x, true);
	});

	$(this.myHandlBut).mousedown(function(e){
		var offset = $(this).offset();
  		var x = parseInt(e.pageX - offset.left);
 		var y = parseInt(e.pageY - offset.top);

	 	this.myObject.mouseDownX = x;//mouseX; mousePos.
 		this.myObject.mouseDownY = y; // mouseY; mousePos.
		
		$(this.myObject.horisSlider).mousemove(function(e){
			var offset2 = $(this).offset();
 			 var xx = parseInt(e.pageX - offset2.left);
  			var yy = parseInt(e.pageY - offset2.top);
			//alert("offY: " + parseInt(offset2.top) + " page: " + parseInt(e.pageY) +  " y= " + yy);
			//this.myObject.myHandlBut.setAttribute("style", "left:" + (xx - this.myObject.mouseDownY) + "px");
			this.myObject.setNewPos(xx - this.myObject.mouseDownY, false);
			
			onSliderMoved(this.myObject.sliderIndex, (xx - this.myObject.mouseDownX));
			return preventEv(e);
		 });
		
		$(this.myObject.horisSlider).mouseup(function(e){
			$(this).unbind('mousemove mouseup mouseout');
			var offset2 = $(this).offset();
 			 var xx = parseInt(e.pageX - offset2.left);
  			var yy = parseInt(e.pageY - offset2.top);
			
			this.myObject.setNewPos(xx - this.myObject.mouseDownX, true);
			return preventEv(e);
		 });

		return preventEv(e);
    }); 
}

SliderHorizontal.prototype.showSlider = function(show) {
	if (show)
		$(this.horisSlider).show();
	else
		$(this.horisSlider).hide();
}

SliderHorizontal.prototype.setNewPos = function(newX, anim) {
	this.currentStep = parseInt(newX/segmentWidth + 0.5);
	var calcX = this.currentStep*segmentWidth -5;
	
	if (anim){
		var strNewX="" + calcX;
		$(this.myHandlBut).animate({left:strNewX},200);
	} else{
		this.myHandlBut.setAttribute("style", "left:" + calcX + "px");
	}
}

function preventEv(e){
		if (e.preventDefault)
        		e.preventDefault();
    	else
        		e.returnValue= false;
    	return false;
	}
	


