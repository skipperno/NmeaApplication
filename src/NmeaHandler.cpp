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
#include "protocol/NewEchoParser.h"

#include "comm/Dispatcher.h"


NmeaHandler* thisInstance;
pthread_mutex_t lastMsgMutex;

int nRange;
int nGain = 1;

NmeaHandler::NmeaHandler() {
	memset(lastMsgStream_1, 0, 17000);
	memset(lastMsgStream_2, 0, 17000);
	nNoOfMessages = 0;
	nNextMsgPos = 0;
	thisInstance = this;
	nRange = 0;
	nStram_1_length = 0;
	nStram_2_length = 0;
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

void NmeaHandler::setRange(int newRange) {
	nRange = newRange;
}

void NmeaHandler::setGain(int newGain) {
	nGain = newGain;
}



bool NmeaHandler::getLastEchoMessage(char* pStream) {
	pthread_mutex_lock(&lastMsgMutex);
	if (lastMsgStream_1[0] != 0) {
		strcpy(pStream, lastMsgStream_1);
		lastMsgStream_1[0] = 0;
		//nNoOfMessages = 0;
		//nNextMsgPos = 0;
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

	int nLastReceivingIndex = 2;

	//int echoLoddNmeaMsgLength;
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
			NewEchoParser::convertDataToAsciNmea(nRange, nGain, pBuffer, length, lastMsgStream_1, &nStram_1_length);
			//BinaryEchoParser::convertCompressedDataToAsciNmea(nRange, pBuffer, length, lastMsgStream_1, &nStram_1_length);

			Dispatcher::sendMsg(lastMsgStream_1, nStram_1_length);
		/*	pthread_mutex_lock(&lastMsgMutex);
			//if(nNoOfMessages < 5) {
			if (nLastReceivingIndex == 2) {
				BinaryEchoParser::convertCompressedDataToAsciNmea(nRange, pBuffer, length, lastMsgStream_1, &nStram_1_length);
				nLastReceivingIndex = 1;
			} else {
				BinaryEchoParser::convertCompressedDataToAsciNmea(nRange, pBuffer, length, lastMsgStream_2, &nStram_2_length);
				nLastReceivingIndex = 2;
			}
			//nNextMsgPos += echoLoddNmeaMsgLength;
				//nNoOfMessages ++;
			//}
			pthread_mutex_unlock(&lastMsgMutex);
			//printf("%s\n", lastMsgStream_1);
			 * */

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
