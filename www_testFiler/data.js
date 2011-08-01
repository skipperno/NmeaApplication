var jsonDATA = 
	{ "type": "ALL",
	  "signal" : 
		{ "GAIN" : 0,
          "TVG"  : 0,
          "FREQ" : "50",
          "POW" : "50"},
      "alarm" : 
  		{ "L" : 44,
          "H" : 55}
    };
/*
var jsonGAIN = 
{ "type": "G",
  "signal" : 
	{ "GAIN" : 0}
};
*/
function setSignalData(){
	menuArray[0].changeValueText(""+jsonDATA.signal.GAIN +"%");
	menuArray[1].changeValueText(""+jsonDATA.signal.TVG +"%");
	menuArray[2].changeValueText(""+jsonDATA.signal.FREQ +"kHz");
	menuArray[3].changeValueText(""+jsonDATA.signal.POW +"%");
	//menuArray[4].changeValueText(""+dataJSON.signal.DRA +"m");
	menuArray[5].changeValueText(""+jsonDATA.alarm.L +"m");
	menuArray[6].changeValueText(""+jsonDATA.alarm.H +"m");
}