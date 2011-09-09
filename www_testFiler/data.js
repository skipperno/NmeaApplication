var jsonDATA = 
	{ "type": "sig",
	  "signal" : 
		{ "GAIN" : 0,
          "TVG"  : 0,
          "FREQ" : "50",
          "POW" : "50"},
      "alarm" : 
  		{ "L" : 44,
          "H" : 1200},
       "range" : 0
    };

var jsonLIGHT = 
{ "type": "LIGHT",
  "brighDay" :[10,20,30,40,50],
  "brighNight" :[0,10,20,30,40],
};

var jsonTOP = 
{ "type": "top",
  "ins" :{"time":"?","gps":"?","speed":"?","frq":"?"}
};

var jsonNmea = 
{ "type": "nmea",
  "nmea" :""
};
/*
var jsonOutput = 
{ 'type': 'out',
  'source':1,
  'omt':['dpt','dbs'],
  'br':{"brRadio":0},
  'dis':{"disRadio":1}
};*/

var jsonOutputs = 
{ 'type': 'out',
  'oms':['dpt','dbs'] // active output msg types
};

var jsonDisplay = 
{ 'type': 'disp',
  'disRadio':{'dis':2}
};

var jsonBaud = 
{ 'type': 'baud',
  'baudR':{'ba':1}
};

function setSignalData(){
	updateMenuValues();
	updateAlarmIcons(); 
}



