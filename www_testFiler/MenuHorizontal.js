

var fastSubMenu;
var subMenuLeft;
var subMenuRight;

var slidingMenu;

var menuArray= new Array();
var subMenuDiv = new Array();
var NUMB_OF_SUBMENU = 4;

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
	
	// SUBMENU 0 (vertical choice: "User setup")
	menuArray[0]=new HorizMenuItem(0, "50m", "ALARM LO", subMenuDiv[0]);	
	menuArray[1]=new HorizMenuItem(1, "400m", "ALARM HI", subMenuDiv[0]);
	menuArray[2]=new HorizMenuItem(2, "line", "MARK", subMenuDiv[0]);
	menuArray[3]=new HorizMenuItem(3, "fwd", "POSITION", subMenuDiv[0]);
	menuArray[4]=new HorizMenuItem(4, "0.00m", "DRAUGHT", subMenuDiv[0]);
	
	// SUBMENU 1 (vertical choice: SIGNAL)
	menuArray[5]=new HorizMenuItem(5, "manual", "MODE", subMenuDiv[1]);	
	menuArray[6]=new HorizMenuItem(6, "50%", "GAIN", subMenuDiv[1]);
	menuArray[7]=new HorizMenuItem(7, "0%", "TVG", subMenuDiv[1]);
	menuArray[8]=new HorizMenuItem(8, "100%", "PWR", subMenuDiv[1]);
	menuArray[9]=new HorizMenuItem(9, "100kHz", "FREQ", subMenuDiv[1]);

	// SUBMENU 2 (vertical choice: Setup)
	menuArray[10]=new HorizMenuItem(10, "small", "COM 1", subMenuDiv[2]);
	menuArray[11]=new HorizMenuItem(11, "line", "COM 2", subMenuDiv[2]);
	menuArray[12]=new HorizMenuItem(12, "off", "LAN", subMenuDiv[2]);
	menuArray[13]=new HorizMenuItem(13, "off", "CAN", subMenuDiv[2]);
	
	
	
	// OLD
	/*
	menuArray[11]=new HorizMenuItem(11, "green", "COLOR", subMenuDiv[2]);
	
	// SUBMENU 3 (NMEA)
	menuArray[12]=new HorizMenuItem(12, "show", "Msg List", subMenuDiv[3]);
	menuArray[13]=new HorizMenuItem(13, "19200", "Baud Rate", subMenuDiv[3]);
	menuArray[14]=new HorizMenuItem(14, "odd", "Parity", subMenuDiv[3]);
	menuArray[15]=new HorizMenuItem(15, "ccc", "ddd", subMenuDiv[3]);
	menuArray[16]=new HorizMenuItem(16, "ppp", "ddd", subMenuDiv[3]);
	*/
	for(i=0;i<NUMB_OF_SUBMENU;i++){
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

function updateMenuValues(){
	menuArray[0].changeValueText(""+jsonDATA.alarm.L +"m");
	menuArray[1].changeValueText(""+jsonDATA.alarm.H +"m");
	
	menuArray[6].changeValueText(""+jsonDATA.signal.GAIN +"%");
	menuArray[7].changeValueText(""+jsonDATA.signal.TVG +"%");
	menuArray[8].changeValueText(""+jsonDATA.signal.POW +"%");
	menuArray[9].changeValueText(""+jsonDATA.signal.FREQ +"kHz");
	
	//menuArray[4].changeValueText(""+dataJSON.signal.DRA +"m");
	
}