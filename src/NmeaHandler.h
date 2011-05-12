/*
 * NmeaHandler.h
 *
 *  Created on: 6. mai 2011
 *      Author: nn
 */

#ifndef NMEAHANDLER_H_
#define NMEAHANDLER_H_

#include "services/SerialPort.h"

class NmeaHandler {
public:
	NmeaHandler();
	virtual ~NmeaHandler();
	void runHandler();

	void getLastXXMessage(char* pStream);
	void getLastWeatherMessage(char* pStream);
	bool getLastEchoMessage(char* pStream);

	static NmeaHandler* getInstance();

private:
	char lastMsgStream_1[10024];
	char lastMsgStream_2[10024];
	SerialPort serialPortEcholodd;
};

#endif /* NMEAHANDLER_H_ */
