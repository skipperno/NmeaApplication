/*
 * NmeaHandler.h
 *
 *  Created on: 6. mai 2011
 *      Author: nn
 */

#ifndef MSGINHANDLER_H_
#define MSGINHANDLER_H_

#include <pthread.h>

#include "comm/SerialPort.h"
#include "comm/SerialCom.h"
#include "Selftest.h"

#define MAX_NMEA_BUFF 17000

class MsgInHandler {
public:
	MsgInHandler();
	virtual ~MsgInHandler();
	void runHandler();

	void getLastXXMessage(char* pStream);
	void getLastWeatherMessage(char* pStream);
	bool getLastEchoMessage(char* pStream);
	bool changeBaudRate_serial3(int newBaud);
	int sendMsgSerial1 (const char* pBuffer, int length);
	int sendMsgSerial2 (const char* pBuffer, int length);
	int sendMsgSerial3 (const char* pBuffer, int length);

	int selfTest(int on_off, int source);
	//void onReceivedNewDisplayChoice(int nSource, int selectedChoice);

	//static void setRange(int nRange);
	//static void setGain(int newGain);

	static MsgInHandler* getInstance();

	//SerialCom serialPortEcholodd;
	SerialCom serialPort3;
private:
	/*void parseRecBuffer();
	void removeFromBuffer(int nRemoveLength);
	void removeUncompletMsg();
	int fineMsgStart();
	int fineMsgEnd(int nStartPos);
*/

	char totalNmeaBuffer[MAX_NMEA_BUFF];
	int totalReceived;

	int nNoOfMessages;
	int nNextMsgPos;

	char lastMsgStream_1[MAX_NMEA_BUFF];
	int nStram_1_length;
	char lastMsgStream_2[MAX_NMEA_BUFF];
	int nStram_2_length;

	Selftest selftest;



	pthread_t threadCurtis;
	pthread_t threadCom3;
};

#endif /* NMEAHANDLER_H_ */
