/***********************************************/
/*********    Main menu (vertical)       *******/
/***********************************************/

var verMenuArray = new Array();
var westMenuSliding;

function initVertMenu(parentConteiner){
	westMenuSliding = this.document.createElement("DIV");
	westMenuSliding.id = "westMenuSliding";
	
	var westMenuTopButt = this.document.createElement("DIV");
	westMenuTopButt.id = "westMenuTopButt";
	$(westMenuTopButt).click(function(e){
		$("#westMenuSliding").animate({top:'0px'},300);
	});
	
	var westMenuDownButt = this.document.createElement("DIV");
	westMenuDownButt.id = "westMenuDownButt";
	$(westMenuDownButt).click(function(e){
		$("#westMenuSliding").animate({top:'-400px'},300);
	});
	
	
	
	verMenuArray[0]=new VerMenuItem(0, "Signal", westMenuSliding);
	verMenuArray[0]=new VerMenuItem(1, "Alarm", westMenuSliding);
	verMenuArray[0]=new VerMenuItem(2, "Skjerm 3", westMenuSliding);
	verMenuArray[0]=new VerMenuItem(3, "Skjerm 4", westMenuSliding);
	verMenuArray[0]=new VerMenuItem(4, "Skjerm 5", westMenuSliding);
	verMenuArray[0]=new VerMenuItem(5, "Skjerm 6", westMenuSliding);
	verMenuArray[0]=new VerMenuItem(6, "Skjerm 7", westMenuSliding);
	verMenuArray[0]=new VerMenuItem(7, "Skjerm 8", westMenuSliding);
	westMenuSliding.appendChild(westMenuDownButt);
	westMenuSliding.appendChild(westMenuTopButt);
	verMenuArray[0]=new VerMenuItem(8, "Skjerm 9", westMenuSliding);
	verMenuArray[0]=new VerMenuItem(9, "Skjerm 10", westMenuSliding);
	verMenuArray[0]=new VerMenuItem(10, "Skjerm 11", westMenuSliding);
	verMenuArray[0]=new VerMenuItem(11, "Skjerm 12", westMenuSliding);
	verMenuArray[0]=new VerMenuItem(12, "Skjerm 13", westMenuSliding);
	verMenuArray[0]=new VerMenuItem(13, "Skjerm 14", westMenuSliding);
	
	parentConteiner.appendChild(westMenuSliding);
}

