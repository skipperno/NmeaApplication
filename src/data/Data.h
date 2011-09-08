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

class Data {

public:
	Data();
	virtual ~Data();

	void setGain(int newGain);
	void setGpsPos(char* n_s, char* sLat, char* e_w, char* sLon);
	void setNmeaMsg(char* nmeaMsg);

	void getJsonData(char* msg);
	void getJsonTop(char* msg);
	void parseJsonMsg(char* msg);
	int getGain();
	int getTvg();
	int getRange();
	void getNmeaData(char* msg);

	static Data* getInstance();
private:
	Object jsonDATA;
	Object jsonTop;
	Object jsonNmea;
	void initSignalData();
	void initTopInfoData();
	void initNmeaScreenData();


/*
	int nGain;
	int nTvg;
	int nFreq;
	int nPower;

	int nAlarm_L;
	int nAlarm_H;*/
};

#endif /* DATA_H_ */
