/*
 * Data.h
 *
 *  Created on: Jul 27, 2011
 *      Author: ernad
 */

#ifndef DATA_H_
#define DATA_H_

#include "DataSignal.h"
#include "DataGlobalt.h"
#include "DataTransceiver.h"

#include "../json/elements.h"
using namespace json;

enum nmeaDirection{
	NMEA_DIRECT_OUT,
	NMEA_DIRECT_IN
};

class Data {

public:
	Data();
	virtual ~Data();

	static Data* getInstance();

	static void setGain(int newGain);
	void setGpsPos(char* n_s, char* sLat, char* e_w, char* sLon);
	void setPowerMeasurment(int nAdcIndex, int value);
	// TODO: wrong place for this function
	void sendNmeaMsg(char* nmeaMsg, int nDirection);

	void getJsonData(char* msg);
	void getJsonTop(char* msg);
	void getJsonTransceiver(char* msg);
	void getJsonActiveTransceiver(char* msg);
	//void getPowerData(char* msg);
	void parseJsonMsg(char* msg);
	int getGain();
	int getTvg();
	int getRange();
	void getNmeaData(char* msg);

	Array getOutputSettingsObject(int inputIndex);
	bool isAlarmMsgEnabled(int inputIndex);
	///////////////////////////////////////////////
	// DEPTH
	///////////////////////////////////////////////
	void setDepthMeters(float fDepth);
	void setSurfaceOffsetMeters(float fOffset);
	void setKeelOffsetMeters(float fOffset);
	float getSurfaceOffsetMeters();
	float getKeelOffsetMeters();

	float getDepthTransMeters();
	float getDepthTransFeet();
	float getDepthTransFathoms();

	float getDepthSurfaceMeters();
	float getDepthSurfaceFeet();
	float getDepthSurfaceFathoms();

	float getDepthKeelMeters();
	float getDepthKeelFeet();
	float getDepthKeelFathoms();


	int getActiveDisplayIndex();
	int getDisplayIoChoice();
	int getAlarmL();
	int getAlarmH();

	char* getLat();
	char* getLon();
	int getVelocity();

	int getBaudCom1();
	int getBaudCom2();
	int getBaudCom3();
	//static int getForwardSourceIndex();
	//static void setForwardSourceIndex(int newIndex);

	DataSignal dataSignal;
	DataGlobalt dataGlobalt;
	DataTransceiver dataTransceiver;
	char configVersion[10];


private:


	void initSignalData();
	void initTopInfoData();
	void initNmeaScreenData();
	void initJsonDisplayData();
	void initJsonBaudData();
	void initIoData();
	void initJsonTestData();
	void initJsonTransceiverData();
	void initJsonActiveTransceiverData();
	void initJsonAlarmConfirmData();
	void initJsonTimeDate();
	void initLightData();
	void initSimulatorData();
	//void initJsonPowerData();

	void changeBaud(int sourceNo, int newBaudIndex);

	///////////////////////////////////////////////
	// DEPTH
	///////////////////////////////////////////////
	float fDepthTransMeters;
	float fSurfaceOffsetMeters;
	float fKeelOffsetMeters;
};

#endif /* DATA_H_ */
