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
  "ins" :{"time":"?","gpsN":"?","gpsE":"?","speed":"?","frq":"?"}
};

var jsonNmea = 
{ "type": "nmea",
   "dir":0,
  "nmea" :""
};

var jsonIO = // used only in start to set saved values
{ 
		'type': 'ioAll',
		'set':[   		
		       		{'type':'1', //COM1
		       		'oms':['a','b','e'], 	// active output msg types
		    	   'disRadio':{'dis':2},	// display: in, out or off
		    	   'baudR':{'ba':1}},
		    	    
		    	   	{'type':'2', //COM2
		    		   "oms":["a","b","e"], 	// active output msg types
			    	 'disRadio':{'dis':2},
			    	 'baudR':{'ba':1}},
			    	 
			    	{'type':'3', //COM3
			    		 "oms":["a","b","e"], 	// active output msg types
				    	 'disRadio':{'dis':2},
				    	 'baudR':{'ba':1}},
				    	 
			    	{'type':'4', //LAN
				     'oms':['a','b','e'], 	// active output msg types
				     'disRadio':{'dis':2}},
				     
				    {'type':'5', //CAN
				    'oms':['a','b','e'], 	// active output msg types
				     'disRadio':{'dis':2},
				     'baudR':{'ba':1}}
			    	]
};

var jsonOutputs = 
{ 'type': 'out',
  'oms':['a','b','e'] // active output msg types
};

var jsonDisplay = 
{ 'type': 'disp',
  'disRadio':{'dis':2},
  's':1    // source
};

var jsonBaud = 
{ 'type': 'baud',
  'baudR':{'ba':1}
};

var jsonTransceiverCH1 = 
{ "type": "transceiverCH1",
  "enabled" : 1, 
  "position": 1, //AFT=0, PORT=1, STUR=1, FWD=3
  "freq1" : 3000, /*!!! freq / 10 **/
  "dualEnabled" : 1,
  "freq2" : 4500 /*!!! freq / 10 **/
};
var jsonTransceiverCH2 = 
{ "type": "transceiverCH2",
  "enabled" : 1, 
  "position": 3, //AFT=0, PORT=1, STUR=1, FWD=3
  "freq1" : 2000, /*!!! freq / 10 **/
  "dualEnabled" : 0,
  "freq2" : 7500 /*!!! freq / 10 **/
};

function setSignalData(){
	updateMenuValues();
	updateAlarmIcons(); 
}



