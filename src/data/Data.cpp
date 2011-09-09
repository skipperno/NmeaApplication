/*
 * Data.cpp
 *
 *  Created on: Jul 27, 2011
 *      Author: ernad
 */

#include "Data.h"

#include <string.h>
#include <stdio.h>

#include "../json/reader.h"
#include "../json/writer.h"
#include "../MsgInHandler.h"
#include "../comm/Dispatcher.h"
#include "../SysTime.h"

#include <sstream>

Data *dataInstance;

/*
 * var jsonDATA =
	{ "type": "ALL",
	  "signal" :
		{ "GAIN" : 0,
          "TVG"  : 0,
          "FREQ" : "50",
          "POW" : "50"},
      "alarm" :
  		{ "L" : 44,
          "H" : 400},
       "range" : 0
    };


var jsonGAIN =
{ "type": "G",
  "signal" :
	{ "GAIN" : 0}
};
 */

Data::Data() {
	dataInstance = this;
	initSignalData();
	initTopInfoData();
	initNmeaScreenData();
	initJsonDisplayData();
	initJsonBaudData();
}

Data::~Data() {

}

Data* Data::getInstance() {
	return dataInstance;
}

void Data::initSignalData(){ // TODO read data from config fil
	jsonDATA["type"]			= String("sig");
	jsonDATA["signal"]["GAIN"]	= Number(50);
	jsonDATA["signal"]["TVG"]	= Number(0);
	jsonDATA["signal"]["FREQ"]	= Number(50);
	jsonDATA["signal"]["POW"]	= Number(8);
	jsonDATA["alarm"]["L"]		= Number(9);
	jsonDATA["alarm"]["H"]		= Number(10);
	jsonDATA["range"] 			= Number(0);
}

void Data::initTopInfoData(){
	GW_TIME timeStruct;
	char newTime[30];
	SysTime::sysTime_get(&timeStruct);

	sprintf(newTime, "%.2d:%.2d:%.2d", timeStruct.gwNewTime.hour, timeStruct.gwNewTime.min, timeStruct.gwNewTime.sec);
	jsonTop["type"]			= String("top");
	jsonTop["ins"]["time"]		= String(newTime);
	jsonTop["ins"]["gps"]		= String("N13,04 S14,2");
	jsonTop["ins"]["speed"]	= Number(332);
	jsonTop["ins"]["frq"]		= Number(10000);
}

void Data::initNmeaScreenData(){ // TODO read data from config fil
	jsonNmea["type"]			= String("nmea");
	jsonNmea["nmea"]	= String("");
}

void Data::initJsonDisplayData(){ // TODO read data from config fil
	jsonDisplay["type"]			= String("disp");
	jsonDisplay["disRadio"]["dis"]	= Number(2); //TODO: get from config
}

void Data::initJsonBaudData(){ // TODO read data from config fil
	jsonBaud["type"]			= String("nmea");
	jsonBaud["baudR"]["ba"]	= Number(0);
}

/*
var jsonLIGHT =
{ "type": "LIGHT",
  "brighDay" :[10,20,30,40,50],
  "brighNight" :[0,10,20,30,40],
};*/


void Data::getJsonData(char* msg){
	 std::stringstream stream;
	 Writer::Write(jsonDATA, stream);
	 strcpy(msg, stream.str().c_str());
}

void Data::getNmeaData(char* msg){
	 std::stringstream stream;
	 Writer::Write(jsonNmea, stream);
	 strcpy(msg, stream.str().c_str());
}

void Data::getJsonTop(char* msg){
	GW_TIME timeStruct;
	char newTime[30];
	SysTime::sysTime_get(&timeStruct);

	sprintf(newTime, "%.2d:%.2d:%.2d", timeStruct.gwNewTime.hour, timeStruct.gwNewTime.min, timeStruct.gwNewTime.sec);
	jsonTop["ins"]["time"] = String(newTime);

	std::stringstream stream;
	Writer::Write(jsonTop, stream);
	strcpy(msg, stream.str().c_str());
}



////////////////////////////////////////////////////
// Receive signal data from one client (browser) and
// broadcast to other clients.
////////////////////////////////////////////////////
void Data::parseJsonMsg(char* msg){
	Object newJson;
	 std::stringstream stream(msg);
	 Reader::Read(newJson, stream);
	 const String ddd= newJson["type"];

	 if(strcmp(ddd.Value().c_str(), "sig") == 0){
		 jsonDATA = newJson;
/*	 	 const Number gain = newJson["signal"]["GAIN"];
	 	 printf ("New GAIN = %d\n", (int)gain.Value());
	 	 MsgInHandler::setGain((int)gain.Value());
*/
	 	 char msgToSend[1000];
	 	 getJsonData(msgToSend);
	 	 Dispatcher::sendConfigMsg(msgToSend, strlen(msgToSend));
	 } else if(strcmp(ddd.Value().c_str(), "baud") == 0){
		 jsonBaud = newJson;
	 }
}

void Data::setNmeaMsg(char* nmeaMsg){
	jsonNmea["nmea"] = String(nmeaMsg);

	char msgToSend[1000];
	getNmeaData(msgToSend);
	Dispatcher::sendConfigMsg(msgToSend, strlen(msgToSend));
}

void Data::setGpsPos(char* n_s, char* sLat, char* e_w, char* sLon){
	char latLong[30];

	sprintf(latLong, "%s%s %s%s", n_s, sLat, e_w, sLon);
	jsonTop["ins"]["gps"] = String(latLong);
}

void Data::setGain(int newGain){
	jsonDATA["signal"]["GAIN"]	= Number(newGain);
}

int Data::getGain(){
	const Number gain = jsonDATA["signal"]["GAIN"];
	return (int)(gain.Value());
}

int Data::getTvg(){
	const Number tvg = jsonDATA["signal"]["TVG"];
	return (int)(tvg.Value());
}

int Data::getRange(){
	const Number range = jsonDATA["range"];
	return (int)(range);
}
