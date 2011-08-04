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
#include "../NmeaHandler.h"
#include "../comm/Dispatcher.h"

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
          "H" : 55}
    };

var jsonGAIN =
{ "type": "G",
  "signal" :
	{ "GAIN" : 0}
};
 */

Data::Data() {
	dataInstance = this;
	initData();
}

Data::~Data() {

}

Data* Data::getInstance() {
	return dataInstance;
}

void Data::initData(){ // TODO read data from config fil
	jsonDATA["type"]			= String("ALL");
	jsonDATA["signal"]["GAIN"]	= Number(50);
	jsonDATA["signal"]["TVG"]	= Number(0);
	jsonDATA["signal"]["FREQ"]	= Number(50);
	jsonDATA["signal"]["POW"]	= Number(8);
	jsonDATA["alarm"]["L"]		= Number(9);
	jsonDATA["alarm"]["H"]		= Number(10);
}

void Data::setGain(int newGain){
	jsonDATA["signal"]["GAIN"]	= Number(newGain);
}

void Data::getJsonData(char* msg){
	 std::stringstream stream;
	 Writer::Write(jsonDATA, stream);
	 strcpy(msg, stream.str().c_str());
}

void Data::parseJsonMsg(char* msg){
	Object newJson;
	 std::stringstream stream(msg);
	 Reader::Read(newJson, stream);
	 const String ddd= newJson["type"];

	 if(strcmp(ddd.Value().c_str(), "ALL") == 0){
		 jsonDATA = newJson;
/*	 	 const Number gain = newJson["signal"]["GAIN"];
	 	 printf ("New GAIN = %d\n", (int)gain.Value());
	 	 NmeaHandler::setGain((int)gain.Value());
*/
	 	 char msgToSend[1000];
	 	 getJsonData(msgToSend);
	 	 Dispatcher::sendConfigMsg(msgToSend, strlen(msgToSend));
	 }
	 /*
	 if(strcmp(ddd.Value().c_str(), "G") == 0){
		 const Number gain = newJson["signal"]["GAIN"];
		 setGain((int)gain.Value());
		 printf ("New GAIN = %d\n", (int)gain.Value());
		 NmeaHandler::setGain((int)gain.Value());
	 }*/
}

int Data::getGain(){
	const Number gain = jsonDATA["signal"]["GAIN"];
	return (int)(gain.Value());
}

int Data::getTvg(){
	const Number tvg = jsonDATA["signal"]["TVG"];
	return (int)(tvg.Value());
}
