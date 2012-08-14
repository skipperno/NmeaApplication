/*
 * ObjectSignal.h
 *
 *  Created on: Mar 13, 2012
 *      Author: ernad
 */

#ifndef DATASIGNAL_H_
#define DATASIGNAL_H_

#include "../json/elements.h"
using namespace json;

class DataSignal {
public:
	DataSignal();
	virtual ~DataSignal();

	void init();
	void updateObjectWithJson(Object jsonSignal);
	void objectToJsonMsg(char* jsonMsg);

	void saveGain(int newValue);
	void saveTvg(int newValue);
	void savePow(int newValue);
	void saveFreq(int newValue);
	void saveAlarmL(int newValue);
	void saveAlarmH(int newValue);
	void saveRange(int newValue);

	int gain;
			int tvg;
			int freq;
			int pow;
			int alarmL;
			int alarmH;
			int range;

private:
	// used when reading config file
		void setGain(const char* gainStr);
		void setTvg(const char* tvgStr);
		void setFreq(const char* freqStr);
		void setPower(const char* powStr);
		void setAlarmL(const char* powStr);
		void setAlarmH(const char* powStr);
		void setRange(const char* powStr);
};

#endif /* OBJECTSIGNAL_H_ */
