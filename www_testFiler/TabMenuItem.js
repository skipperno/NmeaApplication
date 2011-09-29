var testShown = false;

function TabMenuItem(itemIndex, line1, image, parentContainer, enableItem) {
	this.itemIndex= itemIndex;
	this.tabText=line1;
	
	this.parentContainer = parentContainer;
	
	this.document = parentContainer.ownerDocument || parentContainer.document;
	
	
	this.tabItem = this.document.createElement("DIV");
	this.tabItem.className = "tabItem";
	this.tabItem.id = "tabItem_" + itemIndex;
	this.tabItem.parentObject = this;
	
	this.imgDiv = this.document.createElement("img");
	this.imgDiv.src = image;
	//this.imgDiv.className = "pp";
	//this.imgDiv.style.backgroundImage='url(images/home.png)';
	this.tabItem.appendChild(this.imgDiv);
	
	this.tabTextdiv = this.document.createElement("DIV");
	this.tabTextdiv.className = "tabText";
	this.tabTextdiv.innerHTML=this.tabText;
	this.tabItem.appendChild(this.tabTextdiv);
	
	this.parentContainer.appendChild(this.tabItem);
	
	
	if(enableItem) {
		this.enableItem();
	} else {
		this.disableItem();
	}
}

TabMenuItem.prototype.enableItem = function(select){
	this.tabItem.className = "tabItemNotSel";
	
	$(this.tabItem).mouseover(function(e){
		if (!this.parentObject.selected)
			this.parentObject.tabItem.className = "tabItemOver";
			//this.style.backgroundImage='url(images/menuHorOver2.png)';
	});
	
	$(this.tabItem).mouseout(function(e){
		if (!this.parentObject.selected)
			this.parentObject.tabItem.className = "tabItemNotSel";
			//this.style.backgroundImage='url(images/menuHorNotSel2.png)';
	});
	
	$(this.tabItem).click(function(e){
		this.parentObject.tabItem.className = "tabItemSel";
		onHorisontalMenuCallback(this.parentObject.itemIndex);
	});
};

TabMenuItem.prototype.disableItem = function(select){
	$(this.tabItem).unbind('mouseover mouseout click');
	this.tabItem.className = "tabItemDisab";
};

TabMenuItem.prototype.select = function(select){
	if(select){
		this.selected = true;
		this.tabItem.className = "tabItemSel";
		//this.tabItem.style.backgroundImage='url(images/menuHorSel2.png)';
	} else{
		this.selected = false;
		this.tabItem.className = "tabItemNotSel";
		//this.tabItem.style.backgroundImage='url(images/menuHorNotSel2.png)';
	}
};

TabMenuItem.prototype.changeValueText = function(newValue){
		this.tabTextdiv.innerHTML = newValue;
};
