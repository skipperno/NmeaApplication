/**
 * 
 */
var windowWidth=900;

var timeText = [["10", "20", "30", "40", "50", "60"], ["0", "10", "20", "30", "40", "50"], ["0", "20", "40", "60", "80", "100"], 
                 ["0", "100", "200", "300", "400", "500"], ["0", "200", "400", "600", "800", "1000"], ["0", "320", "640", "960", "1280", "1600"]];

var timeTextPos_X= [20, 80, 160, 240, 320, 400];


function changeTimeRange(scale){
	var myElement = document.getElementById('timeScale');
	var inner="";
	
	for(i = 0; i < 6; i++) {
		inner +="<div style=\"width:120px; float:right; color:#fff; border-right:1px solid #fff\">" +
		timeText[scale][i] + "</div>";
	}
		/*while(windowWidth > i*range){
		inner +="<img src=\"images/time.png\" width:\"3px\" style=\"float:right; margin-right:" + range + "px\" />";
		i++
	}*/
	//alert(inner);
	myElement.innerHTML=inner;
	
}