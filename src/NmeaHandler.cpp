/*
 * NmeaHandler.cpp
 *
 *  Created on: 6. mai 2011
 *      Author: nn
 */

#include "NmeaHandler.h"
#include <iostream>
#include <string.h>
#include <pthread.h>

//#include "skipper.h"
#include "NmeaComm.h"
#include "protocol/BinaryEchoParser.h"


NmeaHandler* thisInstance;
pthread_mutex_t lastMsgMutex;

NmeaHandler::NmeaHandler() {
	memset(lastMsgStream_1, 0, 17000);
	memset(lastMsgStream_2, 0, 10024);
	nNoOfMessages = 0;
	nNextMsgPos = 0;
	thisInstance = this;
	nRange = 0;
}

NmeaHandler::~NmeaHandler() {

}

NmeaHandler* NmeaHandler::getInstance() {
	return thisInstance;
}

void NmeaHandler::getLastXXMessage(char* pStream) {

}

void NmeaHandler::getLastWeatherMessage(char* pStream) {
	strcpy(pStream, lastMsgStream_2);
}

void NmeaHandler::setRange(int nRange) {
	this->nRange = nRange;
}

bool NmeaHandler::getLastEchoMessage(char* pStream) {
	if (lastMsgStream_1[0] != 0) {
		strcpy(pStream, lastMsgStream_1);
		nNoOfMessages = 0;
		nNextMsgPos = 0;
		pthread_mutex_unlock(&lastMsgMutex);
		return true;
	} else {
		pthread_mutex_unlock(&lastMsgMutex);
		return false;
	}
}

void NmeaHandler::runHandler() {
	NmeaComm stream1;
	NmeaComm stream2;

	int echoLoddNmeaMsgLength;
	char buffer[10024]; // Storage of NMEA data stream
	char* pBuffer = buffer; // Pointer to storage of NMEA data stream
	int length; // Length of NMEA data stream
/*
	char baudRate[] = "4800"; // Input/output baudrate to be fetched from configuration-file or web-configuration
	char nmea2[] = "2"; // Input NMEA port number to be fetched from configuration-file or web-configuration
	char nmea3[] = "3"; // Input NMEA port number to be fetched from configuration-file or web-configuration
*/
	serialPortEcholodd.configurePort("2", "115200");
	serialPortEcholodd.openInputPort("2");
	serialPortEcholodd.openOutputPort("2");
/*	stream1.NmeaConfigurePort(nmea2, baudRate);
	stream1.NmeaOpenInputPort(nmea2);
	stream1.NmeaOpenOutputPort(nmea2);
	stream2.NmeaConfigurePort(nmea3, baudRate);
	stream2.NmeaOpenInputPort(nmea3);
	stream2.NmeaOpenOutputPort(nmea2);*/

	for (;;) {
		serialPortEcholodd.receive(pBuffer, &length);
		if (length > 0) {
			//printf("Received: %d\n", length);

			serialPortEcholodd.send(pBuffer, length);
			pthread_mutex_lock(&lastMsgMutex);
			//if(nNoOfMessages < 5) {
				BinaryEchoParser::convertCompressedDataToAsciNmea(nRange, pBuffer, length, &lastMsgStream_1[nNextMsgPos], &echoLoddNmeaMsgLength);
				//nNextMsgPos += echoLoddNmeaMsgLength;
				//nNoOfMessages ++;
			//}
			pthread_mutex_unlock(&lastMsgMutex);
			//printf("%s\n", lastMsgStream_1);
		}
		/*
		if (stream1.NmeaInput(pBuffer, &length)) {
			printf("stream1, length %d\n", length);
			stream1.NmeaOutput(pBuffer, length);
			for (i = 0; i < length; i++) {
				if (pBuffer[i] == '\n')
					cout << "<LF>";
				else if (pBuffer[i] == '\r')
					cout << "<CR>";
				else {
					cout << pBuffer[i];
					lastMsgStream_1[i] = pBuffer[i];
				}
			}
			cout << endl;
			if (i > 2)
			 lastMsgStream_1[i - 2] = 0;
		}

		if (stream2.NmeaInput(pBuffer, &length)) {
			printf("stream2, length: %d\n", length);
			stream2.NmeaOutput(pBuffer, length);
			for (i = 0; i < length; i++) {
				if (pBuffer[i] == '\n')
					cout << "<LF>";
				else if (pBuffer[i] == '\r')
					cout << "<CR>";
				else {
					cout << pBuffer[i];
					lastMsgStream_2[i] = pBuffer[i];
				}
			}
			cout << endl;
			if (i > 2)
			 lastMsgStream_2[i - 2] = 0;
		}*/
		usleep(30000);
	}
	serialPortEcholodd.closeInputPort();
	serialPortEcholodd.closeOutputPort();
	/*stream1.NmeaCloseInputPort();
	stream1.NmeaCloseOutputPort();
	stream2.NmeaCloseInputPort();
	stream2.NmeaCloseOutputPort();*/
}
