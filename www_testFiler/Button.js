function Button(itemIndex, parentContainer, line1, line2, iconNorm, iconSelect, iconOver, iconWidth, iconHeight, callbackFunc) {
	this.itemIndex= itemIndex;
	this.text1=line1;

	this.text2 = line2;
	this.selected = false;
	this.parentContainer = parentContainer;
	this.selected = false;
	this.document = parentContainer.ownerDocument || parentContainer.document;
	this.callbackFunc = callbackFunc;
	this.iconNorm = 'url(images/' + iconNorm + ')';
	this.iconSelect = 'url(images/' + iconSelect+ ')';
	if (iconOver != null)
		this.iconOver = 'url(images/' + iconOver+ ')';
	else 
		this.iconOver = null;
	
	this.buttDiv = this.document.createElement("DIV");
	this.buttDiv.className = "buttDiv";
	this.buttDiv.id = "buttDiv" + itemIndex;
	this.buttDiv.parentObject = this;
	this.buttDiv.style.width = iconWidth + "px";
	this.buttDiv.style.height = iconHeight + "px";
	this.buttDiv.style.backgroundImage=this.iconNorm;

	
   this.text1div = this.document.createElement("DIV");
	this.text1div.className = "text1";
	this.text1div.innerHTML=this.text1;
	
	this.text2div = this.document.createElement("DIV");
	this.text2div.className = "text2";
	this.text2div.innerHTML=this.text2;
	
	this.buttDiv.appendChild(this.text1div);
	this.buttDiv.appendChild(this.text2div);
	
	this.parentContainer.appendChild(this.buttDiv);
	
	
	$(this.buttDiv).mouseover(function(e){
		if (!this.parentObject.selected && this.parentObject.iconOver != null)
			this.style.backgroundImage=this.parentObject.iconOver;
	});
	
	$(this.buttDiv).mouseout(function(e){
		if (!this.parentObject.selected)
			this.style.backgroundImage=this.parentObject.iconNorm;
	});
	
	$(this.buttDiv).click(function(e){	
		if(this.parentObject.selected)
			this.parentObject.deselect();
		else
			this.parentObject.select();
		
		this.parentObject.callbackFunc(this.parentObject.itemIndex, this.parentObject.selected);
		return preventEv(e);	
	});
}

Button.prototype.select = function(){
	this.selected = true;
	this.buttDiv.style.backgroundImage=this.iconSelect;
}

Button.prototype.deselect = function(){
	this.selected = false;
	this.buttDiv.style.backgroundImage=this.iconNorm;
}