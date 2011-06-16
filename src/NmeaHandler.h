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
	void setRange(int nRange);

	static NmeaHandler* getInstance();

private:
	int nNoOfMessages;
	int nNextMsgPos;

	char lastMsgStream_1[17000];
	char lastMsgStream_2[10024];
	SerialPort serialPortEcholodd;

	int nRange;
};

#endif /* NMEAHANDLER_H_ */
