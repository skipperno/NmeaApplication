var jsonDATA = 
	{ "type": "sig",
	  "signal" : 
		{ "GAIN" : 0,
          "TVG"  : 0,
          "FREQ" : 50,
          "POW" : 50},
      "alarm" : 
  		{ "L" : 44,
          "H" : 1200},
       "range" : 0
    };

var jsonGet = {
		"type": "getConf"
}

var jsonLIGHT =  /* this is not to send to server. Used only localt for saving of values.*/
{ /*"type": "LIGHT",*/
  "brighDay" :[10,20,30,40,50],
  "brighNight" :[0,10,20,30,40],
};

var jsonLightMsg = /* this is sent in the start and each time user change light */
{ "type": "light",
   "pwm":0
};

var jsonSimulator = /* simulator ON/OFF (OFF = 0, ON = 1) */
{ "type": "simul",
   "sim":0
};

var jsonTOP = 
{ "type": "top",
  "ins" :{"time":"?","gpsN":"?","gpsE":"?","speed":"?","frq":"?"},
  "pow":{"24V_U":"0","24V_I": "0","24_48V_I": "0","5V_U": "0","5V_I": "0","NMEA1_I": "0","NMEA2_I": "0","NMEA3_I": "0"}
};
/*
var jsonPower=
{
	"type":"pow"
	"24V_U": 0,
	"24V_I": 0,  	
    "24/48V_U": 0,
    "5V_U": 0,
    "5V_I": 0,
    "NMEA1_I": 0,
    "NMEA2_I": 0,
    "NMEA3_I": 0
}*/

var jsonNmea = 
{ "type": "nmea",
   "dir":0,
  "nmea" :""
};



var jsonIO = // used only in start to set saved values
{ 
		'type': 'ioAll',
		'set':[   		
		       		{'type':'0', //COM1
		       		 'alOn':0, // alarm NMEA sent via this output
		       		'oms':[0,0,0,0,0], 	// active output msg types
		    	   'outInOff':2,	// display: 0: out, 1: in or 2: off
		    	   'baudR':{'ba':1}},
		    	    
		    	   	{'type':'1', //COM2
		    		   'alOn':0, // alarm NMEA sent via this output
		    		   "oms":[0,0,0,0,0], 	// active output msg types
		    		   'outInOff':2,	// display: 0: out, 1: in or 2: off
			    	 'baudR':{'ba':1}},
			    	 
			    	{'type':'2', //COM3
			    		 'alOn':0, // alarm NMEA sent via this output
			    		 "oms":[0,0,0,0,0], 	// active output msg types
			    		 'outInOff':2,	// display: 0: out, 1: in or 2: off
				    	 'baudR':{'ba':0}},
				    	 
			    	{'type':'3', //LAN
				    		 'alOn':0, // alarm NMEA sent via this output
				     'oms':[0,0,0,0,0], 	// active output msg types
				     'outInOff':2},	// display: 0: out, 1: in or 2: off
				     
				    {'type':'5', //CAN
				    	 'alOn':0, // alarm NMEA sent via this output
				    'oms':[0,0,0,0,0], 	// active output msg types
				    'outInOff':2,	// display: 0: out, 1: in or 2: off
				     'baudR':{'ba':1}}
			    	]
};

var jsonTransceiver = 
{
	'type': 'transceiver',
	'jsonTrans':[{'type': 'transCH1','chEnabled' : 1,'transPos': 1,'freq1' : 3000,'dualEnabled' : 1,'freq2' : 4500},
				 {'type': 'transCH2','chEnabled' : 1,'transPos': 1,'freq1' : 3000,'dualEnabled' : 1,'freq2' : 4500},
				 {'type': 'transCH3','chEnabled' : 1,'transPos': 1,'freq1' : 3000,'dualEnabled' : 1,'freq2' : 4500}, //Extended CH1
				 {'type': 'transCH4','chEnabled' : 1,'transPos': 1,'freq1' : 3000,'dualEnabled' : 1,'freq2' : 4500}],//Extended CH2

/*	'activeCh':3,
	'isActiveDual':0*/
};

var jsonActiveTransceiver = 
{
	'type': 'actTrans',
	'activeCh':3,
	'isActiveDual':0
};
/*
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
};*/

var jsonTestNmea = 
{ 'type': 'test', // test loop- back on NMEA
  'on':1,    // 0 => off, 1 => on
  'source':0    // 0=> NMEA1, 1=> NMEA1, 2=>NMEA3
};

var jsonAlarmConfirm = 
{ 'type': 'alarmConf'
};

function setSignalData(){
	changeRange (jsonDATA.range);
	updateMenuValues();
	updateAlarmIcons(); 
}



