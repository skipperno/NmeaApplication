/*
 * Data.h
 *
 *  Created on: Jul 27, 2011
 *      Author: ernad
 */

#ifndef DATA_H_
#define DATA_H_

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

	void setGain(int newGain);
	void setGpsPos(char* n_s, char* sLat, char* e_w, char* sLon);
	// TODO: wrong place for this function
	void sendNmeaMsg(char* nmeaMsg, int nDirection);

	void getJsonData(char* msg);
	void getJsonTop(char* msg);
	void parseJsonMsg(char* msg);
	int getGain();
	int getTvg();
	int getRange();
	void getNmeaData(char* msg);

	Array getOutputSettingsObject(int inputIndex);

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

	static Data* getInstance();

	static int getActiveDisplayIndex();
	static int getDisplayIoChoice();
	//static int getForwardSourceIndex();
	//static void setForwardSourceIndex(int newIndex);

private:
	Object jsonDATA;
	Object jsonTop;
	Object jsonNmea;
	Object jsonDisplay;
	Object jsonBaud;
	Object jsonIO;

	void initSignalData();
	void initTopInfoData();
	void initNmeaScreenData();
	void initJsonDisplayData();
	void initJsonBaudData();
	void initIoData();

	void changeBaud(int sourceNo, int newBaudIndex);

	///////////////////////////////////////////////
	// DEPTH
	///////////////////////////////////////////////
	float fDepthTransMeters;
	float fSurfaceOffsetMeters;
	float fKeelOffsetMeters;
};

#endif /* DATA_H_ */
