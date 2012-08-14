/*
 * Data.cpp
 *
 *  Created on: Jul 27, 2011
 *      Author: ernad
 */

#include "Data.h"
#include "../definitions.h"
#include <string.h>
#include <stdio.h>

#include "../json/reader.h"
#include "../json/writer.h"
#include "../MsgInHandler.h"
#include "../comm/Dispatcher.h"
#include "../webserver/DataWebSocket.h"
#include "Alarm.h"
#include "FileAccess.h"
#include "ConfigParser.h"
#include "../comm/Backlight.h"

#include "../utility/SysTime.h"
#include "../utility/Log.h"
#include "../MsgInHandler.h"   //TODO: feil plass for å behandle dette
#include <sstream>



//#define DEBUG_ADC

#define METER_FEET_CONST 	3.2808399
#define METER_FATHOM_CONST 	0.546806649

Data *dataInstance = NULL;

int nDisplayIoChoice = -1; // static variable
int nActiveDisplay = -1;



// Object jsonDATA;
Object jsonTop;
Object jsonNmea;
//Object jsonDisplay;
//Object jsonBaud;
Object jsonIO;
Object jsonPower;
Object jsonTransceiver;
Object jsonActTransceiver;
Object jsonTest;
Object jsonAlarmConfirm;
Object jsonTimeDate;
Object jsonLightMsg;
Object jsonSimulate;


int Data::getActiveDisplayIndex() {
	return nActiveDisplay;
}
int Data::getDisplayIoChoice() {
	return nDisplayIoChoice;
}

Data::Data() {
	char temp[30];
	fDepthTransMeters 		= 0;  //TODO: config file
	fSurfaceOffsetMeters 	= 10;
	fKeelOffsetMeters 		= 2;

	FileAccess::createDirectoryIfNotExist(MAIN_CONFIG_DIR);
	FileAccess::createDirectoryIfNotExist(TRANSCEIVER_CONFIG_DIR);
	for (int i = 1; i < 5; i++) {
		sprintf(temp, "%s/%s%d", TRANSCEIVER_CONFIG_DIR, "CH", i);
		FileAccess::createDirectoryIfNotExist(temp);
	}


	dataInstance = this;
	dataSignal.init();
	dataGlobalt.init();
	dataTransceiver.init();

	initTopInfoData();
	initNmeaScreenData();
	//initJsonDisplayData();
	//initJsonBaudData();
	initIoData();
	initJsonTestData();
	initJsonTransceiverData();
	initJsonActiveTransceiverData();
	initJsonAlarmConfirmData();
	initJsonTimeDate();
	initLightData();
	initSimulatorData();
	strcpy(configVersion, DEFAULT_CONFIG_VERSION);

	//initJsonPowerData();
}

Data::~Data() {

}

Data* Data::getInstance() {
	if (dataInstance == NULL)
		dataInstance = new Data();
	return dataInstance;
}

void Data::initJsonTimeDate() {
	jsonTimeDate["type"] = String("tiDay");
	jsonTimeDate["h"] = Number(0);
	jsonTimeDate["min"] = Number(0);
	jsonTimeDate["s"] = Number(0);
	jsonTimeDate["y"] = Number(0);
	jsonTimeDate["m"] = Number(0);
	jsonTimeDate["d"] = Number(0);
}

void Data::initLightData() { // TODO read data from config fil
	jsonLightMsg["type"] = String("light");
	jsonLightMsg["pwm"] = Number(0);

	Backlight::setBacklight(0); // TODO: not right place to do it
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
	jsonTop["ins"]["frq"] = Number(100);

	jsonTop["pow"]["24V_U"] = 		String("0"); 		//voltage
	jsonTop["pow"]["24V_I"] = 		String("0"); 	//current
	jsonTop["pow"]["24_48V_I"] = 	String("0");		//voltage
	jsonTop["pow"]["5V_U"] = 	String("0"); 		//voltage
	jsonTop["pow"]["5V_I"] = 	String("0");		//current
	jsonTop["pow"]["NMEA1_I"] = 		String("0"); 		//current
	jsonTop["pow"]["NMEA2_I"] = 		String("0"); 		//current
	jsonTop["pow"]["NMEA3_I"] = 		String("0");		//current
}

void Data::initNmeaScreenData() { // TODO read data from config fil
	jsonNmea["type"] = String("nmea");
	jsonNmea["dir"] = Number(NMEA_DIRECT_OUT);
	jsonNmea["nmea"] = String("");
}
/*
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

*/
void Data::initJsonAlarmConfirmData() { // TODO read data from config fil
	jsonAlarmConfirm["type"] = String("alarmConf");
}

void Data::initJsonTransceiverData() { // TODO: !!! TRENGER IKKE INIT ???????
	char jsonTransceiverString[1000];
	dataTransceiver.objectToJsonMsg(jsonTransceiverString);


	std::stringstream stream(jsonTransceiverString);
	Reader::Read(jsonTransceiver, stream);
}

void Data::initJsonActiveTransceiverData() {
	char jsonActiveTransceiverString[200];
	dataTransceiver.objectActiveToJsonMsg(jsonActiveTransceiverString);

	std::stringstream stream(jsonActiveTransceiverString);
	Reader::Read(jsonActTransceiver, stream);
}

void Data::initIoData() { // TODO read data from config fil
	char
			jsonIoString[] =
					{
							"{\"type\": \"ioAll\",\"set\":["
								"{\"type\":\"0\",\"alOn\":0,\"oms\":[0,0,0,0,0],\"outInOff\":2,\"baudR\":{\"ba\":1}}," // COM1
								"{\"type\":\"1\",\"alOn\":0,\"oms\":[0,0,0,0,0],\"outInOff\":2,\"baudR\":{\"ba\":1}}," // COM2
								"{\"type\":\"2\",\"alOn\":0,\"oms\":[0,0,0,0,0],\"outInOff\":2,\"baudR\":{\"ba\":1}}," // COM3
								"{\"type\":\"3\",\"alOn\":0,\"oms\":[0,0,0,0,0],\"outInOff\":2}]}" // COM4
					};

	std::stringstream stream(jsonIoString);
	Reader::Read(jsonIO, stream);
}

void Data::initJsonTestData() { // TODO read data from config fil
	jsonTest["type"] = String("test");
	jsonTest["on"] = Number(0);
	jsonTest["source"] = Number(0); //source
}

void Data::initSimulatorData() {
	jsonSimulate["type"] = String("simul");
	jsonSimulate["sim"] = Number(0);
}
/*
void Data::initJsonPowerData() {
	jsonPower["24V_U"] = 		Number(0); 		//voltage
	jsonPower["24V_I"] = 		Number(0);  	//current
	jsonPower["24/48V_U"] = 	Number(0); 		//voltage
	jsonPower["5V_U"] = 		Number(0); 		//voltage
	jsonPower["5V_I"] = 		Number(0); 		//current
	jsonPower["NMEA1_I"] = 		Number(0); 		//current
	jsonPower["NMEA2_I"] = 		Number(0); 		//current
	jsonPower["NMEA3_I"] = 		Number(0); 		//current
}*/





////////////////////////////////////////////////////
// Receive command/data from one client (browser) and
// broadcast to other clients.
////////////////////////////////////////////////////
void Data::parseJsonMsg(char* msg) {
	Object newJson;
	Log::logDbgMsg("!!!!!!!JSON: %s\r\n", msg);

	std::stringstream stream(msg);
	if(!Reader::Read(newJson, stream)){
		printf("No!!!\n");
		return;
	}

	const String ddd = newJson["type"];
	Log::logDbgMsg("JSON type: %s\r\n", ddd.Value().c_str());

	if (strcmp(ddd.Value().c_str(), "getConf") == 0) {
		char msgToSend[1000];
		dataSignal.objectToJsonMsg(msgToSend);
		//getJsonData(msgToSend);
		DataWebSocket::broadcastMsgToClients(msgToSend, strlen(msgToSend));

		getJsonTransceiver(msgToSend);
		DataWebSocket::broadcastMsgToClients(msgToSend, strlen(msgToSend));

		getJsonActiveTransceiver(msgToSend);
		DataWebSocket::broadcastMsgToClients(msgToSend, strlen(msgToSend));
	} else if (strcmp(ddd.Value().c_str(), "sig") == 0) {
		dataSignal.updateObjectWithJson(newJson);
		char msgToSend[1000];
		dataSignal.objectToJsonMsg(msgToSend);
		DataWebSocket::broadcastMsgToClients(msgToSend, strlen(msgToSend));
		FileAccess::notifySettingsChanged();
	} /*else if (strcmp(ddd.Value().c_str(), "baud") == 0) {
		jsonBaud = newJson;
		const Number br = jsonBaud["baudR"]["ba"];

		changeBaud(3, br.Value());
	} else if (strcmp(ddd.Value().c_str(), "disp") == 0) {
		jsonDisplay = newJson;
		const Number selectedDisplayChoice = jsonDisplay["disRadio"]["dis"];
		const Number selectedSource = jsonDisplay["s"];

		MsgInHandler::getInstance()->onReceivedNewDisplayChoice(
				selectedSource.Value(), selectedDisplayChoice.Value());
	}*/ else if (strcmp(ddd.Value().c_str(), "0") == 0) {
		jsonIO["set"][0] = newJson;
		const Number selectedDisplayChoice = newJson["outInOff"];
		nActiveDisplay = 0;
		nDisplayIoChoice = selectedDisplayChoice.Value();
		const Number br = jsonIO["set"][2]["baudR"]["ba"];
		// changeBaud(3, br.Value()); //TODO: only  if not the same baud
	} else if (strcmp(ddd.Value().c_str(), "1") == 0) {
		jsonIO["set"][1] = newJson;
		const Number selectedDisplayChoice = newJson["outInOff"];
		nActiveDisplay = 1;
		nDisplayIoChoice = selectedDisplayChoice.Value();
		const Number br = jsonIO["set"][2]["baudR"]["ba"];
		// changeBaud(3, br.Value()); //TODO: only  if not the same baud
	} else if (strcmp(ddd.Value().c_str(), "2") == 0) {
		jsonIO["set"][2] = newJson;

		const Number selectedDisplayChoice = newJson["outInOff"];

		nActiveDisplay = 2;
		nDisplayIoChoice = selectedDisplayChoice.Value();

		const Number br = jsonIO["set"][2]["baudR"]["ba"];
		changeBaud(3, br.Value()); //TODO: only  if not the same baud
		//MsgInHandler::getInstance()->onReceivedNewDisplayChoice(3,
		//		selectedDisplayChoice.Value());
		printf("!!!!!!!rec JSON type:3, IO choice %d, baud: %d\n", nDisplayIoChoice, (int)br.Value());
	} else if (strcmp(ddd.Value().c_str(), "actTrans") == 0){
		char msgToSend[1000];
		dataTransceiver.updateActiveChObjectWithJson(newJson);
		jsonActTransceiver = newJson;
		/*const Number actCh = jsonActTransceiver["activeCh"];
		const Number isDual = jsonActTransceiver["isActiveDual"];*/
		if (dataTransceiver.isActiveDual == 1) //  isDual.Value() == 1)
			jsonTop["ins"]["frq"] = Number(dataTransceiver.transceiver[dataTransceiver.activeCh].freq2); // Number(jsonTransceiver["jsonTrans"][actCh.Value()]["freq2"]);
		else
			jsonTop["ins"]["frq"] = Number(dataTransceiver.transceiver[dataTransceiver.activeCh].freq1); //Number(jsonTransceiver["jsonTrans"][actCh.Value()]["freq1"]);

		int nPos = dataTransceiver.transceiver[dataTransceiver.activeCh].transPos; //jsonTransceiver["jsonTrans"][actCh.Value()]["transPos"];
		//int nPos = pos.Value();
		if (nPos == 0)
			jsonTop["ins"]["pos"] = String("AFT");
		else if (nPos == 1)
			jsonTop["ins"]["pos"] = String("STRB");
		else if (nPos == 2)
			jsonTop["ins"]["pos"] = String("PORT");
		else
			jsonTop["ins"]["pos"] = String("FWD");

		getJsonActiveTransceiver(msgToSend);
		DataWebSocket::broadcastMsgToClients(msgToSend, strlen(msgToSend));
	} else if (memcmp ( ddd.Value().c_str(), "trans", 5 ) == 0) { //if starts with "trans"
		if (strcmp(ddd.Value().c_str(), "transCH1") == 0)
			dataTransceiver.updateOneChannelWithJson(0, newJson);
		else if (strcmp(ddd.Value().c_str(), "transCH2") == 0)
			dataTransceiver.updateOneChannelWithJson(1, newJson);
		else if (strcmp(ddd.Value().c_str(), "transCH3") == 0) //Extended CH1
			dataTransceiver.updateOneChannelWithJson(2, newJson);
		else if (strcmp(ddd.Value().c_str(), "transCH4") == 0) //Extended CH2
			dataTransceiver.updateOneChannelWithJson(3, newJson);

		char msgToSend[1000];
		// send back for all channels
		dataTransceiver.objectToJsonMsg(msgToSend);
		DataWebSocket::broadcastMsgToClients(msgToSend, strlen(msgToSend));
		/*dataSignal.updateObjectWithJson(newJson);
		char msgToSend[1000];
		dataSignal.objectToJsonMsg(msgToSend);
		DataWebSocket::broadcastMsgToClients(msgToSend, strlen(msgToSend));
		FileAccess::notifySettingsChanged();

		if (strcmp(ddd.Value().c_str(), "transCH1") == 0)
			jsonTransceiver["jsonTrans"][0] = newJson;
		else if (strcmp(ddd.Value().c_str(), "transCH2") == 0)
			jsonTransceiver["jsonTrans"][1] = newJson;
		else if (strcmp(ddd.Value().c_str(), "transCH3") == 0) //Extended CH1
			jsonTransceiver["jsonTrans"][2] = newJson;
		else if (strcmp(ddd.Value().c_str(), "transCH4") == 0) //Extended CH2
			jsonTransceiver["jsonTrans"][3] = newJson;


		getJsonTransceiver(msgToSend);
		DataWebSocket::broadcastMsgToClients(msgToSend, strlen(msgToSend));*/
	} else if (strcmp(ddd.Value().c_str(), "test") == 0) {
		jsonTest = newJson;
		const Number on_off = jsonTest["on"];
		const Number source = jsonTest["source"];
		MsgInHandler::getInstance()->selfTest(on_off.Value(), source.Value());
	} else if (strcmp(ddd.Value().c_str(), "alarmConf") == 0) {
		Alarm::confirmAlarm();
	} else if (strcmp(ddd.Value().c_str(), "tiDay") == 0) {  // User is saving date and time
		SysTime::sysTime_set(((Number)newJson["y"]).Value(), ((Number)newJson["m"]).Value(), ((Number)newJson["d"]).Value(),
				((Number)newJson["h"]).Value(), ((Number)newJson["min"]).Value(), ((Number)newJson["s"]).Value());
	} else if (strcmp(ddd.Value().c_str(), "light") == 0) {
		jsonLightMsg = newJson;
		const Number newLight = jsonLightMsg["pwm"];
		Backlight::setBacklight(newLight.Value());
	} else if (strcmp(ddd.Value().c_str(), "simul") == 0) {
		jsonSimulate = newJson;
		const Number simulate = jsonSimulate["sim"];
		if (simulate.Value() == 1)
			MsgInHandler::getInstance()->simulate(true);
		else
			MsgInHandler::getInstance()->simulate(false);
	}
}


/**
 * sourceNo = 1 => COM1, 2 => COM2, 3 => COM3, 4 => LAN, 5 => CAN
 */
void Data::changeBaud(int sourceNo, int newBaudIndex) { //TODO: not right place for this function
	if (sourceNo == 3) {
		dataGlobalt.saveBaudCom3(newBaudIndex);
		MsgInHandler::getInstance()->restart_serial3();
	}
}

void Data::setGpsPos(char* n_s, char* sLat, char* e_w, char* sLon) {
	char latLong[30];

	sprintf(latLong, "%s %s", n_s, sLat);
	jsonTop["ins"]["gpsN"] = String(latLong);
	sprintf(latLong, "%s %s", e_w, sLon);
	jsonTop["ins"]["gpsE"] = String(latLong);
}




//TODO: ta vekk disse variabler. Brukt med Leif i testing
int nMax = 0;
int nMin = 1000;
int dummyCounter = 0;
void Data::setPowerMeasurment(int nAdcIndex, int value) {
	dummyCounter ++;
	char bufferTemp[20];
	float Vin;// = value*3.3/1023;
	float Vmeas= value*3.3/1023;
	const String vcc_string = jsonTop["pow"]["5V_U"];
	float Vcc_5 = atof(vcc_string.Value().c_str());
#ifdef DEBUG_ADC
	printf("Meas row: %d, Measur. U: %f\n", value, Vmeas);
#endif
	switch(nAdcIndex) {
	case 1:
		sprintf(bufferTemp, "%.2f", (41.7795 - (value*3.3/1023)*7.0518));
		jsonTop["pow"]["24V_U"] = 	String(bufferTemp);
		break;
	case 2:
		// !!! Offset = Vcc_5 * 0.4878   (if Vcc_5 = 5.00V => offset = 2.439V)
		// K = 11

		// Vin = value*3.3/1023
		//Vin = (Vmeas + Vcc_5*470/86.6)*42.25/470;
		//Vin = (Vmeas + Vcc_5*5.4272)*0.08989;
		Vin = (Vmeas*0.08989 + 2.38);
		// ACS714 05B has sensitivity 185mV/A
		//sprintf(bufferTemp, "%.3f", (Vin - Vcc_5/2)/0.185);
		sprintf(bufferTemp, "%.2f", (Vin - 2.5)/0.185);
		jsonTop["pow"]["24V_I"] = 	String(bufferTemp);
#ifdef DEBUG_ADC
		printf("=> Vmeas: %f, Vin_24: %f, 24V_I=%s\n", Vmeas, Vin, bufferTemp);
#endif
			break;
	case 3:
		if (dummyCounter > 300) {
		if (nMax < value)
			nMax = value;
		if (nMin > value)
			nMin = value;
		}
		Vin = (Vmeas + Vcc_5*5.4272)*0.08989;
		//Vin = (Vmeas + Vcc_5*470/86.6)*42.25/470;
		//sprintf(bufferTemp, "%.3f", (Vin - Vcc_5/2 - 0.06)/0.185);
		//sprintf(bufferTemp, "%.3f", (Vin - Vcc_5/2)/0.185);
		sprintf(bufferTemp, "%.2f", (Vin - 2.5)/0.185);
		jsonTop["pow"]["24_48V_I"] = 	String(bufferTemp);
	//	printf("24_48 row: %d\t\t MAX: %d, MIN: %d\n", value, nMax, nMin);
			break;
	case 4:
		// ******************************************************************************
		// 5V_VOLT:
		// V*3.3/1023 / 22000 *(22000 + 15000) =>
		// V*0.005425
		// ******************************************************************************
		sprintf(bufferTemp, "%.2f", (value*0.005425));
		jsonTop["pow"]["5V_U"] = String(bufferTemp);//		Number(((int)(value*0.005425*100)));// /100);
			break;
	case 5:
		// ******************************************************************************
		//5V_CURR:
		// 				  v*1000/(0.5*22100) * 3.3/1023
		// It should be = v /1.105            *3.3/1023   but 0.05 Ohm + PCB track =>
		//              = v /1.172            *3.3/1023 (With PCB-resistance correction)
		//				= v *0.00275239
		// ******************************************************************************
		sprintf(bufferTemp, "%.2f", (value*0.00275));
		jsonTop["pow"]["5V_I"] = 	String(bufferTemp);//	Number(((int)(value*0.00275*1000)));// /1000);
			break;
	case 6:
		sprintf(bufferTemp, "%.2f", (value*3.3/1023/5.7));
		jsonTop["pow"]["NMEA3_I"] = String(bufferTemp);
			break;
	case 7:
		sprintf(bufferTemp, "%.2f", (value*3.3/1023/5.7));
		jsonTop["pow"]["NMEA2_I"] = String(bufferTemp);
			break;
	case 8:
		sprintf(bufferTemp, "%.2f", (value*3.3/1023/5.7));
		jsonTop["pow"]["NMEA1_I"] = String(bufferTemp);
			break;
	}
}

Array Data::getOutputSettingsObject(int inputIndex) {
	return jsonIO["set"][inputIndex]["oms"];
}

bool Data::isAlarmMsgEnabled(int inputIndex) {
	const Number temp  = jsonIO["set"][inputIndex]["alOn"];
	return temp.Value() == 1;
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

void Data::getJsonTransceiver(char* msg){
	dataTransceiver.objectToJsonMsg(msg);
	/*std::stringstream stream;
	Writer::Write(jsonTransceiver, stream);
	strcpy(msg, stream.str().c_str());*/
}

void Data::getJsonActiveTransceiver(char* msg){
	dataTransceiver.objectActiveToJsonMsg(msg);
	/*std::stringstream stream;
	Writer::Write(jsonActTransceiver, stream);
	strcpy(msg, stream.str().c_str());*/
}

/*
void Data::getPowerData(char* msg) {
	std::stringstream stream;
	Writer::Write(jsonPower, stream);
	strcpy(msg, stream.str().c_str());
}*/

int Data::getGain() {
	return dataSignal.gain;
	//const Number gain = jsonDATA["signal"]["GAIN"];
	//return (int) (gain.Value());
}

int Data::getTvg() {
	return dataSignal.tvg;
	//const Number tvg = jsonDATA["signal"]["TVG"];
	//return (int) (tvg.Value());
}

int Data::getRange() {
	return dataSignal.range;
	//const Number range = jsonDATA["range"];
	//return (int) (range);
}

char* Data::getLat() {
	const String aa = jsonTop["ins"]["gpsN"];
	return (char*) aa.Value().c_str();
}

char* Data::getLon() {
	const String aa = jsonTop["ins"]["gpsE"];
	return (char*) aa.Value().c_str();
}

int Data::getVelocity() {
	const Number aa = jsonTop["ins"]["speed"];
	return (int) aa.Value();
}

int Data::getBaudCom1() {
	return dataGlobalt.baudCom1;
}

int Data::getBaudCom2() {
	return dataGlobalt.baudCom2;
}

int Data::getBaudCom3() {
	return dataGlobalt.baudCom3;
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

int Data::getAlarmL(){
	return dataSignal.alarmL;
}

int Data::getAlarmH(){
	return dataSignal.alarmH;
}


// TODO: wrong place for this function
void Data::sendNmeaMsg(char* nmeaMsg, int nDirection) {
	jsonNmea["nmea"] = String(nmeaMsg);
	jsonNmea["dir"] = Number(nDirection);

	char msgToSend[1000];
	getNmeaData(msgToSend);
	DataWebSocket::broadcastMsgToClients(msgToSend, strlen(msgToSend));

	//Dispatcher::sendConfigMsg(msgToSend, strlen(msgToSend));
}

