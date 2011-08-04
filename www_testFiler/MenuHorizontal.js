

var fastSubMenu;
var subMenuLeft;
var subMenuRight;

var slidingMenu;

var menuArray= new Array();
var subMenuDiv = new Array();
var NUMB_OF_SUBMENU = 3;

//$(slidingMenu).animate({left:'-425px'},400);

function initHorisontalSubMenu(){
	
	fastSubMenu = document.createElement("DIV");
	fastSubMenu.id = "fastSubMenu";
	
	slidingMenu = document.createElement("DIV"); //NOT USED
	slidingMenu.id = "slidingMenu";
	
	/*subMenuLeft = this.document.createElement("DIV");
	subMenuLeft.id = "subMenuLeft";
	$(subMenuLeft).click(function(e){
		$(slidingMenu).animate({left:'-425px'},400);
	});
	
	subMenuRight = this.document.createElement("DIV");
	subMenuRight.id = "subMenuRight";
	$(subMenuRight).click(function(e){
		$(slidingMenu).animate({left:'0px'},400);
	});*/
	var i;
	
	for(i=0;i<NUMB_OF_SUBMENU;i++){
		subMenuDiv[i] = document.createElement("DIV");
		subMenuDiv[i].id = "subMenuDiv_"+i;
		subMenuDiv[i].className = "subMenuDiv";
		//subMenuDiv[0].id = "subMenuDiv_0";
	}
	
	// SUBMENU 0 (SIGNAL)
	menuArray[0]=new HorizMenuItem(0, "50%", "GAIN", subMenuDiv[0]);	
	menuArray[1]=new HorizMenuItem(1, "36%", "TVG", subMenuDiv[0]);
	menuArray[2]=new HorizMenuItem(2, "50kHz", "FREQ", subMenuDiv[0]);
	menuArray[3]=new HorizMenuItem(3, "100%", "POWER", subMenuDiv[0]);
	menuArray[4]=new HorizMenuItem(4, "0.00m", "DRAUGHT", subMenuDiv[0]);

	
	// SUBMENU 1 (ALARM)
	menuArray[5]=new HorizMenuItem(5, "50m", "ALARM", subMenuDiv[1]);
	menuArray[6]=new HorizMenuItem(6, "160m", "ALARM", subMenuDiv[1]);

	// SUBMENU 2 (DISPLAY)
	menuArray[7]=new HorizMenuItem(7, "small", "DIGITAL", subMenuDiv[2]);
	menuArray[8]=new HorizMenuItem(8, "line", "MARK", subMenuDiv[2]);
	menuArray[9]=new HorizMenuItem(9, "off", "PRINT", subMenuDiv[2]);
	menuArray[10]=new HorizMenuItem(10, "off", "Scope", subMenuDiv[2]);
	menuArray[11]=new HorizMenuItem(11, "green", "COLOR", subMenuDiv[2]);
	
	for(i=0;i<3;i++){
		fastSubMenu.appendChild(subMenuDiv[i]);
	}
	
	//document.getElementById("subMenu").appendChild(subMenuLeft);
	document.getElementById("subMenu").appendChild(fastSubMenu);
	//document.getElementById("subMenu").appendChild(subMenuRight);
	
	showHorizontalMenu(-1);
}

function deselectHorizontalMenu(menuIndex){
	menuArray[i].select(false);
}

function changeHorMenuButtonValue(menuIndex, newValue){
	menuArray[menuIndex].changeValueText(newValue);
}
/*
function selectHorizontalMenu(menuIndex){
	for(i=0;i<12;i++){
		if(i != menuIndex)
			menuArray[i].select(false);
		else
			menuArray[i].select(true);
	}
}*/

/**
 * 
 * @param submenuIndex index of shown submenu. If -1, submenu is not shown.
 */
function showHorizontalMenu(submenuIndex){
	if (submenuIndex < 0)
		$(fastSubMenu).hide();
	else {
		$(fastSubMenu).show();
		
		for(var i = 0; i<NUMB_OF_SUBMENU;i++){
			if(i==submenuIndex){
				$(subMenuDiv[i]).show();
			} else{
				$(subMenuDiv[i]).hide();
			}
		}
	}
}