
var menuShown = false;
var windowWidth = 900;
var selectedMenuIndex = 1;
var myRange=0;




function changeTimeRange(range){
	var myElement = document.getElementById('timeScale');
	var inner="";
	var i = 1;
	
	
	while(windowWidth > i*range){
		inner +="<img src=\"images/time.png\" width:\"3px\" style=\"float:right; margin-right:" + range + "px\" />";
		i++
	}
	//alert(inner);
	myElement.innerHTML=inner;
	
}

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
	var myMenu = document.getElementById('mainMenu');

	if (!menuShown) {
		menuShown = true;
		myElement.src="images/menu_click.png";
		
					var mySliding1 = new MySliding(1,2,99, 34,  "images/alarm_Up.png", document.getElementById("mainMenu"));
					var mySliding2 = new MySliding(2,2,99, 34,  "images/alarm_down.png", document.getElementById("mainMenu"));
					var mySliding3 = new MySliding(3,2,99, 34,  "images/screenSpeed.png", document.getElementById("mainMenu"));
					var mySliding4 = new MySliding(4,2,99, 34,  "images/slider4.png", document.getElementById("mainMenu"));
	/*				
                    
		myMenu.innerHTML="<img src=\"images/menu2.png\" id=\"menuBut1\" onmouseover=\"onMenuOver(1)\" onmouseout=\"onMenuOut(1)\" onclick=\"onMenuClick(1)\"/>" +
                "<img src=\"images/menu2.png\" id=\"menuBut2\" onmouseover=\"onMenuOver(2)\" onmouseout=\"onMenuOut(2)\" onclick=\"onMenuClick(2)\"/>" +
                "<img src=\"images/menu2.png\" id=\"menuBut3\" onmouseover=\"onMenuOver(3)\" onmouseout=\"onMenuOut(3)\" onclick=\"onMenuClick(3)\"/>" +
                "<img src=\"images/menu2.png\" id=\"menuBut4\" onmouseover=\"onMenuOver(4)\" onmouseout=\"onMenuOut(4)\" onclick=\"onMenuClick(4)\"/>";*/
	} else {
		menuShown = false;
		myElement.src="images/menu.png";
		myMenu.innerHTML="";
	}
}

function onMenuOver(buttIndex) {
	if (selectedMenuIndex != buttIndex) {
	var myElement = document.getElementById('menuBut' + buttIndex);
	myElement.src="images/menu_foc.png";
	}
}
function onMenuOut(buttIndex) {
	if (selectedMenuIndex != buttIndex) {
	var myElement = document.getElementById('menuBut' + buttIndex);
	myElement.src="images/menu2.png";
	}
}
function onMenuClick(buttIndex) {
	
	var myElement = document.getElementById('menuBut' + buttIndex);
	if (selectedMenuIndex != buttIndex) {
		diselectMenuButtons();
		myElement.src="images/menu_click.png";
		selectedMenuIndex = buttIndex;
		onMenuChanged(buttIndex);
	}
}

function onMenuChanged(buttIndex) {
	var leftElement = document.getElementById('leftMenu');//artic_1');
	var myHtml = "";
	if (buttIndex == 1) {
		myHtml = "<div class=\"slider\" id=\"slider-1\" tabIndex=\"1\">" +
   						+"<input class=\"slider-input\" id=\"slider-input-1\"  name=\"slider-input-1\"/>" +
						+"</div>";
  
		leftElement.innerHTML = myHtml;

		var s = new Slider(document.getElementById("slider-1"),  document.getElementById("slider-input-1"), "vertical");
		s.setMinimum(0);
		s.setMaximum(100);
		s.setValue(50);
	} else {
		leftElement.innerHTML = "";
	}
	
	
}

function diselectMenuButtons() {
	for (i=1; i<5;i++){
		document.getElementById('menuBut' + i).src="images/menu2.png";
	}
}
