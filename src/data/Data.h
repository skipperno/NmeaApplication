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
	void getJsonData(char* msg);
	void parseJsonMsg(char* msg);
	int getGain();
	int getTvg();
	static Data* getInstance();
private:
	Object jsonDATA;
	void initData();


/*
	int nGain;
	int nTvg;
	int nFreq;
	int nPower;

	int nAlarm_L;
	int nAlarm_H;*/
};

#endif /* DATA_H_ */
