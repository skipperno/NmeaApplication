/*
 * NmeaHandler.h
 *
 *  Created on: 6. mai 2011
 *      Author: nn
 */

#ifndef NMEAHANDLER_H_
#define NMEAHANDLER_H_

#include "comm/SerialPort.h"

class NmeaHandler {
public:
	NmeaHandler();
	virtual ~NmeaHandler();
	void runHandler();

	void getLastXXMessage(char* pStream);
	void getLastWeatherMessage(char* pStream);
	bool getLastEchoMessage(char* pStream);
	static void setRange(int nRange);
	static void setGain(int newGain);

	static NmeaHandler* getInstance();

private:
	int nNoOfMessages;
	int nNextMsgPos;

	char lastMsgStream_1[17000];
	int nStram_1_length;
	char lastMsgStream_2[17000];
	int nStram_2_length;
	SerialPort serialPortEcholodd;
};

#endif /* NMEAHANDLER_H_ */
