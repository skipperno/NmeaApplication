var testShown = false;

function HorizMenuItem(itemIndex, line1, line2, parentContainer) {
	this.itemIndex= itemIndex;
	this.text1=line1;
	this.text2 = line2;
	
	this.parentContainer = parentContainer;
	
	this.document = parentContainer.ownerDocument || parentContainer.document;
	
	
	this.menuItem = this.document.createElement("DIV");
	this.menuItem.className = "menuItem";
	this.menuItem.id = "menuItem_" + itemIndex;
	
	this.text1div = this.document.createElement("DIV");
	this.text1div.className = "text1";
	this.text1div.innerHTML=this.text1;
	
	this.text2div = this.document.createElement("DIV");
	this.text2div.className = "text2";
	this.text2div.innerHTML=this.text2;
	
	this.menuItem.appendChild(this.text1div);
	this.menuItem.appendChild(this.text2div);
	
	this.parentContainer.appendChild(this.menuItem);
	
	$(this.menuItem).click(function(e){
		if(testShown){
			$("#testCont").hide();
			testShown = false;
		}else{
			$("#testCont").show();
			testShown = true;
		}
	});
}
/**********************
	VERTICAL
 */
function VerMenuItem(itemIndex, itemText, parentContainer) {
	this.itemIndex= itemIndex;
	this.itemText=itemText;
	this.selected=false;
	
	this.parentContainer = parentContainer;
	
	this.document = parentContainer.ownerDocument || parentContainer.document;
	
	
	this.verMenuItem = this.document.createElement("DIV");
	this.verMenuItem.className = "verMenuItem";
	this.verMenuItem.id = "verMenuItem_" + itemIndex;
	this.verMenuItem.parentObject = this;
	
	this.verTextDiv = this.document.createElement("DIV");
	this.verTextDiv.className = "verTextDiv";
	this.verTextDiv.innerHTML=this.itemText;
	
	this.verMenuItem.appendChild(this.verTextDiv);
	
	this.parentContainer.appendChild(this.verMenuItem);
	
	$(this.verMenuItem).mouseover(function(e){
		if (!this.parentObject.selected)
			this.style.backgroundImage='url(images/VerMenuItemBackroundOver.png)';
	});
	
	$(this.verMenuItem).mouseout(function(e){
		if (!this.parentObject.selected)
			this.style.backgroundImage='url(images/VerMenuItemBackround.png)';
	});
	
	$(this.verMenuItem).click(function(e){
		onMainMenuClickCallback(this.parentObject.itemIndex);
	});
}

VerMenuItem.prototype.select = function(select){
	if(select){
		this.selected = true;
		this.verMenuItem.style.backgroundImage='url(images/VerMenuItemBackroundSelect.png)';
	} else{
		this.selected = false;
		this.verMenuItem.style.backgroundImage='url(images/VerMenuItemBackround.png)';
	}
}