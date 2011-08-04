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

#include "data/DataProcessing.h"
#include "data/ButterworthLowPassFilter.h"


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
char testArr[]={70,67,75,78,79,77,68,71,70,57,58,73,70,68,66,66,68,72,69,68,71,63,71,77,72,72,62,60,81,79,54,67,69,71,71,78,79,76,71,72,71,91,87,83,75,79,72,94,91,89,82,86,86,85,85,97,95,96,73,87,73,79,81,84,84,72,59,66,59,66,63,58,87,87,81,79,69,70,78,78,61,55,65,76,73,60,64,72,75,75,80,66,63,44,66,60,67,68,68,76,76,47,67,61,65,70,79,83,83,73,58,57,58,67,68,81,78,85,75,67,65,72,64,77,75,81,94,93,90,78,86,85,83,89,83,80,70,64,69,71,71,60,68,84,80,77,62,83,77,84,69,82,78,87,87,67,81,92,82,69,80,72,65,73,82,71,67,81,93,85,74,73,86,67,71,91,91,77,72,73,86,97,79,79,80,72,77,83,86,86,82,100,100,85,81,81,90,87,86,108,107,89,98,89,97,95,85,86,68,96,94,97,66,99,100,100,93,88,91,91,97,78,85,100,100,106,91,98,100,108,94,102,102,103,91,115,92,99,84,110,105,87,109,113,97,100,95,82,60,75,85,77,77,74,74,92,74,70,69,55,65,70,68,76,76,84,77,77,74,62,80,78,65,69,75,74,85,86,75,77,73,87,85,71,86,66,87,97,90,74,88,86,94,95,80,89,95,104,110,111,93,100,102,118,119,118,115,115,120,119,125,121,122,120,120,108,121,128,131,131,127,122,124,146,144,131,134,139,132,125,135,145,135,139,142,147,159,146,138,137,136,124,125,128,153,153,146,151,141,152,149,151,159,153,144,160,153,163,140,161,165,161,154,138,158,159,150,148,163,166,166,181,185,182,191,193,189,190,191,194,197,180,193,196,197,162,103,106,104,108,107,102,105,76,62,78,83,76,59,78,70,75,72,61,71,70,80,77,67,76,83,87,87,70,72,73,87,88,72,78,89,91,86,81,62,73,72,54,69,76,66,86,85,73,82,82,50,77,74,77,65,68,49,60,70,84,78,71,64,66,55,56,72,73,70,62,72,55,66,63,62,65,56,54,58,58,56,49,74,70,80,67,70,75,56,57,73,66,73,64,64,65,71,71,75,80,82,76,81,87,73,68,80,81,72,71,72,78,84,95,76,73,81,82,60,65,75,75,67,54,65,64,10};
	for (;;) {
		serialPortEcholodd.receive(pBuffer, &length);
		if (length > 0) {
			char outArray[400];
			serialPortEcholodd.send(pBuffer, length);
			//DataProcessing::kalmanFilter(pBuffer, 400, outArray);
			// ButterworthLowPassFilter::test(outArray, 400, outArray);
			int nButtom = DataProcessing::bottomDetection(pBuffer, 400);
			//NewEchoParser::convertDataToAsciNmea(nRange, nGain, testArr, 400, lastMsgStream_1, &nStram_1_length);
			NewEchoParser::convertDataToAsciNmea(nButtom, nRange, nGain, pBuffer, length, lastMsgStream_1, &nStram_1_length);


			//BinaryEchoParser::convertCompressedDataToAsciNmea(nRange, pBuffer, length, lastMsgStream_1, &nStram_1_length);

			Dispatcher::sendEchoMsg(lastMsgStream_1, nStram_1_length);
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
