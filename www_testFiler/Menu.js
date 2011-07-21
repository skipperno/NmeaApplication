
var menuShown = false;
var selectedMenuIndex = 1;

function onMainMenuClickCallback(menuIndex){
	showSubmenu(menuIndex);
}

function initMenu(){
	
	initHorisontalSubMenu();
	setMenuShown(false);
}

/***********************************************/
/*********    Button Setup/Exit Menu     *******/
/***********************************************/
function enableMenuOver() {
	if (!menuShown) {
		var myElement = document.getElementById('enbMenuBut');
		myElement.src="images/menu_foc.png";
	}
}
function enableMenuOut() {
	if (!menuShown) {
	var myElement = document.getElementById('enbMenuBut');
	myElement.src="images/menu.png";
	}
}
function enableMenuClick() {
	var myElement = document.getElementById('enbMenuBut');
	
	if (menuShown) {
		setMenuShown(false);
		myElement.src="images/menu.png";
	}else{
		setMenuShown(true);
		myElement.src="images/go-back-icon_black.png";
	}
}

function setMenuShown(show){
	if(show){
		showSubmenu(0);
		$(westMenuSliding).show();
	} else{
		showSubmenu(-1);
		$(westMenuSliding).hide();
	}
	menuShown = show;
}


