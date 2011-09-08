/***********************************************/
/*********    Main menu (vertical)       *******/
/***********************************************/

var verMenuArray = new Array();
var vertMenuSliding;

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
	
	
	
	verMenuArray[0]=new VerMenuItem(0, "User setup", vertMenuSlidingBlock_1);
	verMenuArray[1]=new VerMenuItem(1, "Signal", vertMenuSlidingBlock_1);
	verMenuArray[2]=new VerMenuItem(2, "Setup", vertMenuSlidingBlock_1);
	vertMenuSlidingBlock_1.appendChild(westMenuDownButt);
	
	vertMenuSlidingBlock_2.appendChild(westMenuTopButt);
	verMenuArray[3]=new VerMenuItem(3, "Status", vertMenuSlidingBlock_2);
	verMenuArray[4]=new VerMenuItem(4, "Com", vertMenuSlidingBlock_2);
	verMenuArray[5]=new VerMenuItem(5, "Diagnostic", vertMenuSlidingBlock_2);
	verMenuArray[6]=new VerMenuItem(6, "Screen", vertMenuSlidingBlock_2);
	verMenuArray[7]=new VerMenuItem(7, "System", vertMenuSlidingBlock_2);
	
	
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
