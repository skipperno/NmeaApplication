/*
 * DataTransceiver.h
 *
 *  Created on: Aug 10, 2012
 *      Author: ernad
 */

#ifndef DATATRANSCEIVER_H_
#define DATATRANSCEIVER_H_

#include "../json/elements.h"
using namespace json;

//'chEnabled' : 0,'transPos': 1,'freq1' : 3000,'dualEnabled' : 0,'freq2' : 4000
typedef struct {
	int chEnabled;
	int transPos; // 0 = "AFT", 1 = "STRB", 2 = "PORT", 3 = "FWD"
	int freq1;
	int dualEnabled;
	int freq2;
} transceiverStruct;

class DataTransceiver {
public:
	DataTransceiver();
	virtual ~DataTransceiver();
	transceiverStruct transceiver[4]; // 0 = CH1, 1=CH2, 2=EXT CH1, 3=EXT CH2
	int activeCh;
	int isActiveDual;

	void init();

	bool setTransceiverEnabled(int nIndex, int nValue);
	void saveTransceiverEnabled(int nIndex, int nValue);

	bool setTransceiverPos(int nIndex, int nValue);
	void saveTransceiverPos(int nIndex, int nValue);

	bool setTransceiverFreq(int nTransIndex, bool dual, int nValue);
	void saveTransceiverFreq(int nTransIndex, bool dual, int nValue);

	bool setDualEnabled(int nTransIndex, int nValue);
	void saveDualEnabled(int nTransIndex, int nValue);

	void updateObjectWithJson(Object jsonSignal);
	// pga. bug i Firefox, sender bare en channel
	void updateOneChannelWithJson(int nIndex, Object jsonTransceiverOneChannel);
	void objectToJsonMsg(char* jsonMsg);
	void objectActiveToJsonMsg(char* jsonMsg); // active transceiver channel
	void updateActiveChObjectWithJson(Object jsonActTransceiver);

	bool setActiveChannel(int nTransIndex);
	void saveActiveChannel(int nTransIndex);

	bool setActiveChannelIsDual(int nValue);
	void saveActiveChannelIsDual(int nValue);
};

#endif /* DATATRANSCEIVER_H_ */
