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
#include "../MsgInHandler.h"   //TODO: feil plass for å behandle dette
#include <sstream>

#define METER_FEET_CONST 	3.2808399
#define METER_FATHOM_CONST 	0.546806649

Data *dataInstance;

int nDisplayIoChoice = -1; // static variable
int nActiveDisplay = -1;



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

int Data::getActiveDisplayIndex() {
	return nActiveDisplay;
}
int Data::getDisplayIoChoice() {
	return nDisplayIoChoice;
}
/*
void Data::setActiveDisplayIndex(int newIndex) {
	nActiveDisplay = newIndex;
}
*/
Data::Data() {
	fDepthTransMeters 		= 0;  //TODO: config file
	fSurfaceOffsetMeters 	= 10;
	fKeelOffsetMeters 		= 2;

	dataInstance = this;
	initSignalData();
	initTopInfoData();
	initNmeaScreenData();
	initJsonDisplayData();
	initJsonBaudData();
	initIoData();
}

Data::~Data() {

}

Data* Data::getInstance() {
	return dataInstance;
}

void Data::initSignalData() { // TODO read data from config fil
	jsonDATA["type"] = String("sig");
	jsonDATA["signal"]["GAIN"] = Number(50);
	jsonDATA["signal"]["TVG"] = Number(0);
	jsonDATA["signal"]["FREQ"] = Number(50);
	jsonDATA["signal"]["POW"] = Number(8);
	jsonDATA["alarm"]["L"] = Number(9);
	jsonDATA["alarm"]["H"] = Number(10);
	jsonDATA["range"] = Number(0);
}

void Data::initTopInfoData() {
	GW_TIME timeStruct;
	char newTime[30];
	SysTime::sysTime_get(&timeStruct);

	sprintf(newTime, "%.2d:%.2d:%.2d", timeStruct.gwNewTime.hour,
			timeStruct.gwNewTime.min, timeStruct.gwNewTime.sec);
	jsonTop["type"] = String("top");
	jsonTop["ins"]["time"] = String(newTime);
	jsonTop["ins"]["gpsN"] = String("?");
	jsonTop["ins"]["gpsE"] = String("?");
	jsonTop["ins"]["speed"] = Number(332);
	jsonTop["ins"]["frq"] = Number(10000);
}

void Data::initNmeaScreenData() { // TODO read data from config fil
	jsonNmea["type"] = String("nmea");
	jsonNmea["dir"] = Number(NMEA_DIRECT_OUT);
	jsonNmea["nmea"] = String("");
}

void Data::initJsonDisplayData() { // TODO read data from config fil
	jsonDisplay["type"] = String("disp");
	jsonDisplay["disRadio"]["dis"] = Number(2); //TODO: get from config
	jsonBaud["s"] = Number(0); //source
}

void Data::initJsonBaudData() { // TODO read data from config fil
	jsonBaud["type"] = String("nmea");
	jsonBaud["baudR"]["ba"] = Number(0);
	jsonBaud["s"] = Number(0); //source
}

void Data::initIoData() { // TODO read data from config fil
	char
			jsonIoString[] =
					{
							"{\"type\": \"ioAll\",\"set\":["
								"{\"type\":\"1\",\"oms\":[\"a\",\"e\"],\"disRadio\":{\"dis\":2},\"baudR\":{\"ba\":1}}," // COM1
								"{\"type\":\"2\",\"oms\":[\"a\",\"e\"],\"disRadio\":{\"dis\":2},\"baudR\":{\"ba\":1}}," // COM2
								"{\"type\":\"3\",\"oms\":[\"a\",\"b\",\"e\"],\"disRadio\":{\"dis\":2},\"baudR\":{\"ba\":1}}," // COM3
								"{\"type\":\"4\",\"oms\":[\"a\",\"e\"],\"disRadio\":{\"dis\":2}}," // COM4
								"{\"type\":\"5\",\"oms\":[\"a\",\"e\"],\"disRadio\":{\"dis\":2},\"baudR\":{\"ba\":1}}]}" // COM5
					};

	std::stringstream stream(jsonIoString);
	Reader::Read(jsonIO, stream);
}

Array Data::getOutputSettingsObject(int inputIndex) {
	return jsonIO["set"][inputIndex]["oms"];
}

/*
 var jsonLIGHT =
 { "type": "LIGHT",
 "brighDay" :[10,20,30,40,50],
 "brighNight" :[0,10,20,30,40],
 };*/

void Data::getJsonData(char* msg) {
	std::stringstream stream;
	Writer::Write(jsonDATA, stream);
	strcpy(msg, stream.str().c_str());
}

void Data::getNmeaData(char* msg) {
	std::stringstream stream;
	Writer::Write(jsonNmea, stream);
	strcpy(msg, stream.str().c_str());
}

void Data::getJsonTop(char* msg) {
	GW_TIME timeStruct;
	char newTime[30];
	SysTime::sysTime_get(&timeStruct);

	sprintf(newTime, "%.2d:%.2d:%.2d", timeStruct.gwNewTime.hour,
			timeStruct.gwNewTime.min, timeStruct.gwNewTime.sec);
	jsonTop["ins"]["time"] = String(newTime);

	std::stringstream stream;
	Writer::Write(jsonTop, stream);
	strcpy(msg, stream.str().c_str());
}

////////////////////////////////////////////////////
// Receive signal data from one client (browser) and
// broadcast to other clients.
////////////////////////////////////////////////////
void Data::parseJsonMsg(char* msg) {
	Object newJson;
	std::stringstream stream(msg);
	Reader::Read(newJson, stream);
	const String ddd = newJson["type"];

	if (strcmp(ddd.Value().c_str(), "sig") == 0) {
		jsonDATA = newJson;
		/*	 	 const Number gain = newJson["signal"]["GAIN"];
		 printf ("New GAIN = %d\n", (int)gain.Value());
		 MsgInHandler::setGain((int)gain.Value());
		 */
		char msgToSend[1000];
		getJsonData(msgToSend);
		Dispatcher::sendConfigMsg(msgToSend, strlen(msgToSend));
	} else if (strcmp(ddd.Value().c_str(), "baud") == 0) {
		jsonBaud = newJson;
		const Number br = jsonBaud["baudR"]["ba"];

		changeBaud(3, br.Value());
	} /*else if (strcmp(ddd.Value().c_str(), "disp") == 0) {
		jsonDisplay = newJson;
		const Number selectedDisplayChoice = jsonDisplay["disRadio"]["dis"];
		const Number selectedSource = jsonDisplay["s"];

		MsgInHandler::getInstance()->onReceivedNewDisplayChoice(
				selectedSource.Value(), selectedDisplayChoice.Value());
	}*/ else if (strcmp(ddd.Value().c_str(), "1") == 0) {
		jsonIO["set"][0] = newJson;

		Array tempA = jsonIO["set"][0]["oms"];
		String tempS;
		for (unsigned int i = 0; i<tempA.Size(); i++){
			tempS = tempA[i];
			printf("0: i=%d oms= %s\n", i, tempS.Value().c_str());
		}
		nActiveDisplay = 1;
	} else if (strcmp(ddd.Value().c_str(), "2") == 0) {
		jsonIO["set"][1] = newJson;
		Array tempA = jsonIO["set"][1]["oms"];
		String tempS;
		for (unsigned int i = 0; i<tempA.Size(); i++){
			tempS = tempA[i];
			printf("1: i=%d oms= %s\n", i, tempS.Value().c_str());
		}
		nActiveDisplay = 2;
	} else if (strcmp(ddd.Value().c_str(), "3") == 0) {
		jsonIO["set"][2] = newJson;

		const Number selectedDisplayChoice =
				jsonIO["set"][2]["disRadio"]["dis"];

		nActiveDisplay = 3;
		nDisplayIoChoice = selectedDisplayChoice.Value();

		const Number br = jsonIO["set"][2]["baudR"]["ba"];
		changeBaud(3, br.Value()); //TODO: only  if not the same baud
		//MsgInHandler::getInstance()->onReceivedNewDisplayChoice(3,
		//		selectedDisplayChoice.Value());
	}
}

/**
 * sourceNo = 1 => COM1, 2 => COM2, 3 => COM3, 4 => LAN, 5 => CAN
 */
void Data::changeBaud(int sourceNo, int newBaudIndex) { //TODO: not right place for this function
	if (newBaudIndex == 0)
		MsgInHandler::getInstance()->changeBaudRate_serial3(4800);
	else if (newBaudIndex == 1)
		MsgInHandler::getInstance()->changeBaudRate_serial3(9600);
	else if (newBaudIndex == 2)
		MsgInHandler::getInstance()->changeBaudRate_serial3(38400);
	else if (newBaudIndex == 3)
		MsgInHandler::getInstance()->changeBaudRate_serial3(115200);
}

// TODO: wrong place for this function
void Data::sendNmeaMsg(char* nmeaMsg, int nDirection) {
	jsonNmea["nmea"] = String(nmeaMsg);
	jsonNmea["dir"] = Number(nDirection);

	char msgToSend[1000];
	getNmeaData(msgToSend);
	Dispatcher::sendConfigMsg(msgToSend, strlen(msgToSend));
}

void Data::setGpsPos(char* n_s, char* sLat, char* e_w, char* sLon) {
	char latLong[30];

	sprintf(latLong, "%s %s", n_s, sLat);
	jsonTop["ins"]["gpsN"] = String(latLong);
	sprintf(latLong, "%s %s", e_w, sLon);
	jsonTop["ins"]["gpsE"] = String(latLong);
}

void Data::setGain(int newGain) {
	jsonDATA["signal"]["GAIN"] = Number(newGain);
}

int Data::getGain() {
	const Number gain = jsonDATA["signal"]["GAIN"];
	return (int) (gain.Value());
}

int Data::getTvg() {
	const Number tvg = jsonDATA["signal"]["TVG"];
	return (int) (tvg.Value());
}

int Data::getRange() {
	const Number range = jsonDATA["range"];
	return (int) (range);
}



////////////////////////////////////////////////////////////////////////
// DEPTH
////////////////////////////////////////////////////////////////////////
void Data::setDepthMeters(float fDepth) {
	fDepthTransMeters = fDepth;
}
void Data::setSurfaceOffsetMeters(float fOffset) {
	fSurfaceOffsetMeters = fOffset;
}
void Data::setKeelOffsetMeters(float fOffset) {
	fKeelOffsetMeters = fOffset;
}

float Data::getSurfaceOffsetMeters() {
	return fSurfaceOffsetMeters;
}

float Data::getKeelOffsetMeters() {
	return fKeelOffsetMeters;
}

float Data::getDepthTransMeters() {
	return fDepthTransMeters;
}
float Data::getDepthTransFeet() {
	return fDepthTransMeters * 3.2808399;
}
float Data::getDepthTransFathoms() {
	return fDepthTransMeters * 0.546806649;
}

float Data::getDepthSurfaceMeters() {
	return (fDepthTransMeters + fSurfaceOffsetMeters);
}

float Data::getDepthSurfaceFeet() {
	return getDepthSurfaceMeters() * METER_FEET_CONST;
}
float Data::getDepthSurfaceFathoms() {
	return getDepthSurfaceMeters() * METER_FATHOM_CONST;
}

float Data::getDepthKeelMeters() {
	return (fDepthTransMeters - fKeelOffsetMeters);
}
float Data::getDepthKeelFeet() {
	return getDepthKeelMeters() * METER_FEET_CONST;
}
float Data::getDepthKeelFathoms() {
	return getDepthKeelMeters() * METER_FATHOM_CONST;
}

