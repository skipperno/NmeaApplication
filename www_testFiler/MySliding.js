// JavaScript Document

//&var increasingId=1;

MySliding.isSupported = typeof document.createElement != "undefined" &&
	typeof document.documentElement != "undefined" &&
	typeof document.documentElement.offsetWidth == "number";


function MySliding (slidIndex, slMin, slMax, slStart, imgUrl, parentContainer) {
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
	
	this.mySlidImg = this.document.createElement("img");
	this.mySlidImg.setAttribute('src', imgUrl);
	this.mySlidImg.setAttribute('alt', 'alternate text');
	this.mySlidImg.setAttribute('width', '50px');
	this.mySlidImg.setAttribute('height', '80px');
	this.mySlidImg.setAttribute('margin-right', '20px');
	//this.mySlidImg.setAttribute('width', '100px');

	this.mySlidDiv = this.document.createElement("DIV");
	
	this.mySlidDiv.className = "mySlid";
	this.mySlidDiv.id = "mySlidId_" + this.myId;
	this.mySlidDiv.unselectable = "on";
	this.mySlidDiv.myObject = this;
	//this.mySlidDiv.style.background='#bbe';
	
		this.myLine = this.document.createElement("DIV");
		this.myLine.className = "mySlidLine";
		this.myLine.unselectable = "on";
		
		this.myHandlBut = this.document.createElement("DIV");
		this.myHandlBut.className = "mySlidHandlBut";
		this.myHandlBut.id = "myHandlButId_" + this.myId;
		this.myHandlBut.myObject = this;
		this.myHandlBut.unselectable = "on";

		//this.mySlidDiv.appendChild(this.myLine);
		this.mySlidDiv.appendChild(this.myHandlBut);
		
		this.mySlidConteiner.appendChild(this.mySlidImg);
		this.mySlidConteiner.appendChild(this.mySlidDiv);
		
		this.parentContainer.appendChild(this.mySlidConteiner);
	
	
	
	//this.myHandlBut.onmouseover	= MySliding.eventHandlers.onmouseover;
	//this.myHandlBut.onmouseout		= MySliding.eventHandlers.onmouseout;
	//this.myHandlBut.onmousedown		= MySliding.eventHandlers.onmousedown;
	
	

	$(this.myHandlBut).mousedown(function(e){
		//var mousePos = getMouseXY(this.id, e.pageX, e.pageY);
		 var offset = $(this).offset();
  var x = parseInt(e.pageX - offset.left);
  var y = parseInt(e.pageY - offset.top);
  
		
		/*var offset=$(this).offset();
		var mouseX = e.pageX - (offset.left); //this.offsetLeft)
		var mouseY =e.pageY - (offset.top);  //this.offsetTop*/
 /*     var clientCoords = "( " + (e.clientX - this.offsetLeft)
+ ", " + (e.clientY - this.offsetTop)+ " )"; */
	 	this.myObject.mouseDownX = x;//mouseX; mousePos.
 		this.myObject.mouseDownY = y; // mouseY; mousePos.
		
		$(this.myObject.mySlidDiv).mousemove(function(e){
			var offset2 = $(this).offset();
 			 var xx = parseInt(e.pageX - offset2.left);
  			var yy = parseInt(e.pageY - offset2.top);
			//alert("offY: " + parseInt(offset2.top) + " page: " + parseInt(e.pageY) +  " y= " + yy);
			this.myObject.myHandlBut.setAttribute("style", "top:" + (yy - this.myObject.mouseDownY) + "px");
			e.stopPropagation();
			//onSliderMoved(this.myObject.sliderIndex, (yy - this.myObject.mouseDownY));
		 });
		
		$(this.myObject.mySlidDiv).mouseup(function(e){
			$(this).unbind('mousemove mouseup mouseout');
			e.stopPropagation();
			var offset2 = $(this).offset();
			 var xx = parseInt(e.pageX - offset2.left);
 			var yy = parseInt(e.pageY - offset2.top);
 			
			onSliderMoved(this.myObject.sliderIndex, (yy - this.myObject.mouseDownY));
		 });
		
		/*$(this.myObject.mySlidDiv).mouseout(function(e){
													 alert("Out");
			$(this).unbind('mousemove mouseup mouseout');
			e.stopPropagation();
		 });*/
		
		e.stopPropagation();
		/*
	 	if (this.parentNode.addEventListener) {
			
		
			//this.parentNode.addEventListener("mousemove", MySliding.eventHandlers.onmousemove, true);
			this.parentNode.addEventListener("mouseup", MySliding.eventHandlers.onmouseup, true);
			this.parentNode.addEventListener("mouseout", MySliding.eventHandlers.onmouseout, true);
			//alert("added1");
		}
		else if (e.srcElement.document.attachEvent) { // for IE
			this.parentNode.attachEvent("onmousemove", MySliding.eventHandlers.onmousemove);
			this.parentNode.attachEvent("onmouseup", MySliding.eventHandlers.onmouseup);
			this.parentNode.attachEvent("onlosecapture", MySliding.eventHandlers.onmouseup);
			this.parentNode.attachEvent("onmouseout", MySliding.eventHandlers.onmouseout);
			//alert("added2");
			//s.element.setCapture();
		}*/
    }); 
	
	/*									  
	$("#aaaa").mousedown(function(e){  //div
      var pageCoords = "( " + (e.pageX - this.offsetLeft)
+ ", " + (e.pageY - this.offsetTop)+ " )"; 
      var clientCoords = "( " + (e.clientX - this.offsetLeft)
+ ", " + (e.clientY - this.offsetTop)+ " )"; 
      $("span:first").text("( e.pageX, e.pageY ) - " + pageCoords); 
      $("span:last").text("( e.clientX, e.clientY ) - " + clientCoords); 
    }); */
	
	
	//parentContainer
}

////////////////////////////////////////////////////
// JQuery: get relative X and Y
////////////////////////////////////////////////////
// Example
// var aaa =  getMouseXY("baby", e.pageX, e.pageY);
// aaa.x
function getMouseXY(elementID, mouseX, mouseY) {
  var offset = $('#'+elementID).offset();
  var x = parseInt(mouseX - offset.left);
  var y = parseInt(mouseY - offset.top);

  return {'x': x, 'y': y};
}
