/*
 * NmeaHandler.cpp
 *
 *  Created on: 6. mai 2011
 *      Author: nn
 */

#include "NmeaHandler.h"
#include <iostream>
#include <string.h>
//#include "skipper.h"
#include "NmeaComm.h"

NmeaHandler* thisInstance;

NmeaHandler::NmeaHandler() {
	memset(lastMsgStream_1, 0, 10024);
	memset(lastMsgStream_2, 0, 10024);
	thisInstance = this;
}

NmeaHandler::~NmeaHandler() {
	// TODO Auto-generated destructor stub
}

NmeaHandler* NmeaHandler::getInstance() {
	return thisInstance;
}

void NmeaHandler::getLastXXMessage(char* pStream) {

}

void NmeaHandler::getLastWeatherMessage(char* pStream) {
	strcpy(pStream, lastMsgStream_2);
}

bool NmeaHandler::getLastEchoMessage(char* pStream) {
	if (lastMsgStream_1[0] != 0) {
		strcpy(pStream, lastMsgStream_1);
		return true;
	} else {
		return false;
	}
}

void NmeaHandler::runHandler() {
	NmeaComm stream1;
	NmeaComm stream2;

	char stream[10024]; // Storage of NMEA data stream
	char* pStream = stream; // Pointer to storage of NMEA data stream
	int length, i; // Length of NMEA data stream

	char baud4800[] = "4800"; // Input/output baudrate to be fetched from configuration-file or web-configuration
	char nmea2[] = "2"; // Input NMEA port number to be fetched from configuration-file or web-configuration
	char nmea3[] = "3"; // Input NMEA port number to be fetched from configuration-file or web-configuration

	stream1.NmeaConfigurePort(nmea2, baud4800);
	stream1.NmeaOpenInputPort(nmea2);
	stream1.NmeaOpenOutputPort(nmea2);
	stream2.NmeaConfigurePort(nmea3, baud4800);
	stream2.NmeaOpenInputPort(nmea3);
	stream2.NmeaOpenOutputPort(nmea2);

	for (;;) {

		if (stream1.NmeaInput(pStream, &length)) {
			printf("stream1, length %d\n", length);
			stream1.NmeaOutput(pStream, length);
			for (i = 0; i < length; i++) {
				if (pStream[i] == '\n')
					cout << "<LF>";
				else if (pStream[i] == '\r')
					cout << "<CR>";
				else {
					cout << pStream[i];
					lastMsgStream_1[i] = pStream[i];
				}
			}
			cout << endl;
			if (i > 2)
			 lastMsgStream_1[i - 2] = 0;
		}

		if (stream2.NmeaInput(pStream, &length)) {
			printf("stream2, length: %d\n", length);
			stream2.NmeaOutput(pStream, length);
			for (i = 0; i < length; i++) {
				if (pStream[i] == '\n')
					cout << "<LF>";
				else if (pStream[i] == '\r')
					cout << "<CR>";
				else {
					cout << pStream[i];
					lastMsgStream_2[i] = pStream[i];
				}
			}
			cout << endl;
			if (i > 2)
			 lastMsgStream_2[i - 2] = 0;
		}
		usleep(300000);
	}

	stream1.NmeaCloseInputPort();
	stream1.NmeaCloseOutputPort();
	stream2.NmeaCloseInputPort();
	stream2.NmeaCloseOutputPort();
}
