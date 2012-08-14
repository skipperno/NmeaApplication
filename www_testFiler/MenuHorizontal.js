

var fastSubMenu;
var subMenuLeft;
var subMenuRight;

var slidingMenu;

var menuArray= new Array();
var subMenuDiv = new Array();


/*
var AL_L = 0;
var AL_H = 1;
var MARK = 2;
var POSITION = 3;
var DRAUGHT = 4;
var MODE = 5;*/
var GAIN = 0;
var TVG = 1;
var PWR = 2;
var COM1 = 3;
var COM2 = 4;
var LAN = 5;
var CAN = 6;
var COLOR = 7;
var TRANSCEIVER = 8;
var HARDWARE = 9;
var SIMULATOR = 10;
var SCOPE = 11;
var NUMB_OF_HOR_MENU = 12;
//$(slidingMenu).animate({left:'-425px'},400);

function initHorisontalSubMenu(){
	
	fastSubMenu = document.createElement("DIV");
	fastSubMenu.id = "fastSubMenu";
	
	slidingMenu = document.createElement("DIV"); //NOT USED
	slidingMenu.id = "slidingMenu";

	var i;
	
	for(i=0;i<NUMB_OF_VERT_MENU;i++){
		subMenuDiv[i] = document.createElement("DIV");
		subMenuDiv[i].id = "subMenuDiv_"+i;
		subMenuDiv[i].className = "subMenuDiv";
	}

	
	
	// SUBMENU 0 (vertical choice: ADJUST)
//	menuArray[MODE]=new HorizMenuItem(MODE, "manual", "MODE", subMenuDiv[ADJUST]);	
	menuArray[GAIN]=new HorizMenuItem(GAIN, "50%", "GAIN", subMenuDiv[ADJUST]);
	menuArray[TVG]=new HorizMenuItem(TVG, "0%", "TVG", subMenuDiv[ADJUST]);
	menuArray[PWR]=new HorizMenuItem(PWR, "100%", "PWR", subMenuDiv[ADJUST]);
//	menuArray[FREQ]=new HorizMenuItem(FREQ, "100kHz", "FREQ", subMenuDiv[ADJUST]);
	
	//(vertical choice: TRANSDUCER): None horizontal menu
	//(vertical choice: ALARMS): None horizontal menu
	//(vertical choice: MARK): None horizontal menu
	
	// SUBMENU 0 (vertical choice: "User setup")
/*	menuArray[AL_L]=new HorizMenuItem(AL_L, "50m", "ALARM LO", subMenuDiv[USER_SETUP]);	
	menuArray[AL_H]=new HorizMenuItem(AL_H, "400m", "ALARM HI", subMenuDiv[USER_SETUP]);
	menuArray[MARK]=new HorizMenuItem(MARK, "line", "MARK", subMenuDiv[USER_SETUP]);
	menuArray[POSITION]=new HorizMenuItem(POSITION, "fwd", "POSITION", subMenuDiv[USER_SETUP]);
	menuArray[DRAUGHT]=new HorizMenuItem(DRAUGHT, "0.00m", "DRAUGHT", subMenuDiv[USER_SETUP]);*/

	// SUBMENU 2 (vertical choice: Setup)
	menuArray[COM1]=new HorizMenuItem(COM1, "small", "COM 1", subMenuDiv[COM]);
	menuArray[COM2]=new HorizMenuItem(COM2, "line", "COM 2", subMenuDiv[COM]);
	menuArray[LAN]=new HorizMenuItem(LAN, "off", "LAN", subMenuDiv[COM]);
	menuArray[CAN]=new HorizMenuItem(CAN, "off", "CAN", subMenuDiv[COM]);
	
	menuArray[COLOR]=new HorizMenuItem(COLOR, "", "COLOR", subMenuDiv[SYSTEM_SETUP]);
	
	menuArray[TRANSCEIVER]=new HorizMenuItem(TRANSCEIVER, "", "TRANSC", subMenuDiv[SYSTEM_SETUP]);
	menuArray[HARDWARE]=new HorizMenuItem(HARDWARE, "", "HARDWARE", subMenuDiv[SYSTEM_SETUP]);
menuArray[SIMULATOR]=new HorizMenuItem(SIMULATOR, "OFF", "SIMULATOR", subMenuDiv[DIAGN]);
menuArray[SCOPE]=new HorizMenuItem(SCOPE, "OFF", "SCOPE", subMenuDiv[DIAGN]);
	
	for(i=0;i<NUMB_OF_VERT_MENU;i++){
		fastSubMenu.appendChild(subMenuDiv[i]);
	}
	
	//document.getElementById("subMenu").appendChild(subMenuLeft);
	document.getElementById("subMenu").appendChild(fastSubMenu);
	//document.getElementById("subMenu").appendChild(subMenuRight);
	
	showHorizontalMenu(-1);
}


function changeHorMenuButtonValue(menuIndex, newValue){
	menuArray[menuIndex].changeValueText(newValue);
}


/**
 * 
 * @param submenuIndex index of shown submenu. If -1, submenu is not shown.
 */
function showHorizontalMenu(submenuIndex){
	if (submenuIndex < 0){
		deselectOtherHorizontalMenuItems(-1);// deselect all
		//$(fastSubMenu).hide();
		$("#subMenu").hide();
	} else {
		//$(fastSubMenu).show();
		$("#subMenu").show();
		for(var i = 0; i<NUMB_OF_VERT_MENU;i++){
			if(i==submenuIndex){
				$(subMenuDiv[i]).show();
			} else{
				$(subMenuDiv[i]).hide();
			}
		}
	}
}

function updateMenuValues(){
/*	menuArray[0].changeValueText(""+jsonDATA.alarm.L +"m");
	menuArray[1].changeValueText(""+jsonDATA.alarm.H +"m");
	*/
	menuArray[GAIN].changeValueText(""+jsonDATA.signal.GAIN +"%");
	menuArray[TVG].changeValueText(""+jsonDATA.signal.TVG +"%");
	menuArray[PWR].changeValueText(""+jsonDATA.signal.POW +"%");
	//menuArray[9].changeValueText(""+jsonDATA.signal.FREQ +"kHz");
	
	//menuArray[4].changeValueText(""+dataJSON.signal.DRA +"m");
	
}

function deselectOtherHorizontalMenuItems(submenuIndex){
		for(i=0;i<NUMB_OF_HOR_MENU;i++){
			if(i != submenuIndex)
				menuArray[i].deselect();
		}
}
