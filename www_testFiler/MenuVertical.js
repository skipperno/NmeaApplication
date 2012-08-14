/***********************************************/
/*********    Main menu (vertical)       *******/
/***********************************************/

var verMenuArray = new Array();
var vertMenuSliding;

var ALARMS = 0;
var PICT_SPEED = 1;
var MARK = 2;
var TRANSDUCER = 3;
var ADJUST = 4;

var SETUP = 5;
var STATUS = 6;
var COM = 7;
var DIAGN = 8;
var SYSTEM_SETUP = 9;


var NUMB_OF_VERT_MENU = 10;


function initVertMenu(parentConteiner){
	vertMenuSliding = this.document.createElement("DIV");
	vertMenuSliding.id = "vertMenuSliding";
	
	vertMenuSlidingBlock_1 = this.document.createElement("DIV");
	vertMenuSlidingBlock_1.className = "vertMenuSlidingBlock";
	vertMenuSlidingBlock_1.id = "vertMenuSlidingBlock_1";
	vertMenuSliding.appendChild(vertMenuSlidingBlock_1);
	
	vertMenuSlidingBlock_2 = this.document.createElement("DIV");
	vertMenuSlidingBlock_2.className = "vertMenuSlidingBlock";
	vertMenuSlidingBlock_2.id = "vertMenuSlidingBlock_2";
	vertMenuSliding.appendChild(vertMenuSlidingBlock_2);
	
	vertMenuSlidingBlock_3 = this.document.createElement("DIV");
	vertMenuSlidingBlock_3.className = "vertMenuSlidingBlock";
	vertMenuSlidingBlock_3.id = "vertMenuSlidingBlock_3";
	vertMenuSliding.appendChild(vertMenuSlidingBlock_3);
	
	
	var westMenuTopButt = this.document.createElement("DIV");
	westMenuTopButt.id = "westMenuTopButt";
	$(westMenuTopButt).click(function(e){
		removeSlider();
		$("#vertMenuSliding").animate({top:'0px'},300);
	});
	
	var westMenuDownButt = this.document.createElement("DIV");
	westMenuDownButt.id = "westMenuDownButt";
	$(westMenuDownButt).click(function(e){
		removeSlider();
		$("#vertMenuSliding").animate({top:'-400px'},300);
	});
	
	verMenuArray[ALARMS]=new VerMenuItem(ALARMS, "Alarm", vertMenuSlidingBlock_1);
	verMenuArray[PICT_SPEED]=new VerMenuItem(PICT_SPEED, "Screen Time", vertMenuSlidingBlock_1);
	verMenuArray[MARK]=new VerMenuItem(MARK, "Mark", vertMenuSlidingBlock_1);
	verMenuArray[TRANSDUCER]=new VerMenuItem(TRANSDUCER, "Transducer", vertMenuSlidingBlock_1);
	verMenuArray[ADJUST]=new VerMenuItem(ADJUST, "Adjust", vertMenuSlidingBlock_1);

	
	vertMenuSlidingBlock_1.appendChild(westMenuDownButt);
	
	vertMenuSlidingBlock_2.appendChild(westMenuTopButt);
	
	verMenuArray[SETUP]=new VerMenuItem(SETUP, "Setup", vertMenuSlidingBlock_2);
	verMenuArray[STATUS]=new VerMenuItem(STATUS, "Status", vertMenuSlidingBlock_2);
	verMenuArray[COM]=new VerMenuItem(COM, "Com", vertMenuSlidingBlock_2);
	verMenuArray[DIAGN]=new VerMenuItem(DIAGN, "Diagnostic", vertMenuSlidingBlock_2);
	verMenuArray[SYSTEM_SETUP]=new VerMenuItem(SYSTEM_SETUP, "System Setup", vertMenuSlidingBlock_2);
	
/*	
	verMenuArray[8]=new VerMenuItem(8, "Skjerm 9", vertMenuSlidingBlock_2);
	verMenuArray[9]=new VerMenuItem(9, "Skjerm 10", vertMenuSlidingBlock_2);
	verMenuArray[10]=new VerMenuItem(10, "Skjerm 11", vertMenuSlidingBlock_3);
	verMenuArray[11]=new VerMenuItem(11, "Skjerm 12", vertMenuSlidingBlock_3);
	verMenuArray[12]=new VerMenuItem(12, "Skjerm 13", vertMenuSlidingBlock_3);
	verMenuArray[13]=new VerMenuItem(13, "Skjerm 14", vertMenuSlidingBlock_3);
	*/
	parentConteiner.appendChild(vertMenuSliding);
	
	verMenuArray[0].select(true);
}

function resetVertMenu(){
	$("#vertMenuSliding").css("top","0px");
	selectVerticalMenu(-1);
	selectedVerticalMenuIndex = -1;
}

function selectVerticalMenu(submenuIndex){
	for(var i=0;i<NUMB_OF_VERT_MENU;i++){
		if(i != submenuIndex)
			verMenuArray[i].select(false);
		else {
			verMenuArray[i].select(true);
		}
	}
}

