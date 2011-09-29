/***********************************************/
/*********    Main menu (vertical)       *******/
/***********************************************/

var verMenuArray = new Array();
var vertMenuSliding;

var USER_SETUP = 0;
var SIGNAL = 1;
var SETUP = 2;
var STATUS = 3;
var COM = 4;
var DIAGN = 5;
var SCREEN = 6;
var SYSTEM = 7;


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
		$("#vertMenuSliding").animate({top:'0px'},300);
	});
	
	var westMenuDownButt = this.document.createElement("DIV");
	westMenuDownButt.id = "westMenuDownButt";
	$(westMenuDownButt).click(function(e){
		$("#vertMenuSliding").animate({top:'-400px'},300);
	});
	
	
	verMenuArray[USER_SETUP]=new VerMenuItem(USER_SETUP, "User setup", vertMenuSlidingBlock_1);
	verMenuArray[SIGNAL]=new VerMenuItem(SIGNAL, "Signal", vertMenuSlidingBlock_1);
	verMenuArray[SETUP]=new VerMenuItem(SETUP, "Setup", vertMenuSlidingBlock_1);
	vertMenuSlidingBlock_1.appendChild(westMenuDownButt);
	
	vertMenuSlidingBlock_2.appendChild(westMenuTopButt);
	verMenuArray[STATUS]=new VerMenuItem(STATUS, "Status", vertMenuSlidingBlock_2);
	verMenuArray[COM]=new VerMenuItem(COM, "Com", vertMenuSlidingBlock_2);
	verMenuArray[DIAGN]=new VerMenuItem(DIAGN, "Diagnostic", vertMenuSlidingBlock_2);
	verMenuArray[SCREEN]=new VerMenuItem(SCREEN, "Screen", vertMenuSlidingBlock_2);
	verMenuArray[SYSTEM]=new VerMenuItem(SYSTEM, "System", vertMenuSlidingBlock_2);
	
	
	verMenuArray[8]=new VerMenuItem(8, "Skjerm 9", vertMenuSlidingBlock_2);
	verMenuArray[9]=new VerMenuItem(9, "Skjerm 10", vertMenuSlidingBlock_2);
	verMenuArray[10]=new VerMenuItem(10, "Skjerm 11", vertMenuSlidingBlock_3);
	verMenuArray[11]=new VerMenuItem(11, "Skjerm 12", vertMenuSlidingBlock_3);
	verMenuArray[12]=new VerMenuItem(12, "Skjerm 13", vertMenuSlidingBlock_3);
	verMenuArray[13]=new VerMenuItem(13, "Skjerm 14", vertMenuSlidingBlock_3);
	
	parentConteiner.appendChild(vertMenuSliding);
	
	verMenuArray[0].select(true);
}


function selectVerticalMenu(submenuIndex){
	for(i=0;i<14;i++){
		if(i != submenuIndex)
			verMenuArray[i].select(false);
		else {
			verMenuArray[i].select(true);
		}
	}
}
