

var fastTranscSubMenu;

var transcMenuArray= new Array();
var subMenuDivTransc = new Array();
var NUMB_OF_SUBMENU_TRANSC = 1; // use only if sliding

var selectedTransceiverMenuIndex = -1;
//$(slidingMenu).animate({left:'-425px'},400);

function onHorisontalMenuCallbackTest(tabIndex) {
	showChannel(tabIndex + 1);
	//selectTransceiverTabMenu(tabIndex, true);
}

function initTransceiverMenu(parentDiv){
	
	fastTranscSubMenu = document.createElement("DIV");
	fastTranscSubMenu.id = "tabBar";

	
	var i;
	
	for(i=0;i<NUMB_OF_SUBMENU_TRANSC;i++){ // only if sliding
		subMenuDivTransc[i] = document.createElement("DIV");
		subMenuDivTransc[i].id = "subMenuDivTransc_"+i;
		subMenuDivTransc[i].className = "subMenuDivTransc";
		//subMenuDivTransc[0].id = "subMenuDivTransc_0";
	}
	
	// SUBMENU 0 (SIGNAL)
	transcMenuArray[0]=new TabMenuItem(0, "CH1", "", subMenuDivTransc[0], true);	
	transcMenuArray[1]=new TabMenuItem(1, "CH2", "", subMenuDivTransc[0], true);
	transcMenuArray[2]=new TabMenuItem(2, "Ext CH1", "", subMenuDivTransc[0], false);
	transcMenuArray[3]=new TabMenuItem(3, "Ext CH2", "", subMenuDivTransc[0]), false;
	
	//for(i=0;i<NUMB_OF_SUBMENU_TRANSC;i++){
		fastTranscSubMenu.appendChild(subMenuDivTransc[0]);
	//}
	
	//document.getElementById("subMenu").appendChild(subMenuLeft);
		parentDiv.appendChild(fastTranscSubMenu);
	//document.getElementById("subMenu").appendChild(subMenuRight);
	
	showTransceiverTabSubMenu(0);
}


function selectTransceiverTabMenu(menuIndex, select){
	transcMenuArray[menuIndex].select(select);
	if(select)
		selectedTransceiverMenuIndex = menuIndex;
}

/**
 * 
 * @param submenuIndex index of shown submenu. If -1, submenu is not shown.
 */
function showTransceiverTabSubMenu(submenuIndex){ // only if sliding
	if (submenuIndex < 0)
		$(fastTranscSubMenu).hide();
	else {
		$(fastTranscSubMenu).show();
		
		for(var i = 0; i<NUMB_OF_SUBMENU_TRANSC;i++){
			if(i==submenuIndex){
				$(subMenuDivTransc[i]).show();
			} else{
				$(subMenuDivTransc[i]).hide();
			}
		}
	}
}