/*
 * NewEchoParser.cpp
 *
 *  Created on: Jul 14, 2011
 *      Author: ernad
 */

#include "NewEchoParser.h"
#include <string.h>
#include <stdio.h>

int VERTICAL_RESOLUTION = 400;

NewEchoParser::NewEchoParser() {
	// TODO Auto-generated constructor stub

}

NewEchoParser::~NewEchoParser() {
	// TODO Auto-generated destructor stub
}

void NewEchoParser::convertDataToAsciNmea(int nRange, char* inBuffer, int inLength, char* asciNmeaMsg, int * nAsciMsgLength) {
	char averageBuffer[VERTICAL_RESOLUTION + 2]; // 2 for header (1- type, 2-range)
	//convertCompressedDataToAverage(nRange, compressedBuffer, nCompressedLength, averageBuffer);

	NewEchoParser::convertAverageToAsciNmea(nRange, inBuffer, asciNmeaMsg, nAsciMsgLength);
}


void NewEchoParser::convertAverageToAsciNmea(int nRange, char* averageBuffer, char* asciNmeaMsg, int * nAsciMsgLength) {
	asciNmeaMsg[0] = '1'; // TODO: msg type
	asciNmeaMsg[1] = 0x30 + nRange;

	*nAsciMsgLength = 2;

	for (int i = 0; i < VERTICAL_RESOLUTION; i++) {
		if (averageBuffer[i] > 99) {
			asciNmeaMsg[(*nAsciMsgLength)++] = 0x30 + averageBuffer[i] / 100;
			asciNmeaMsg[(*nAsciMsgLength)++] = 0x30 + (averageBuffer[i] % 100) / 10;
			asciNmeaMsg[(*nAsciMsgLength)++] = 0x30 + averageBuffer[i] % 10;
		} else if (averageBuffer[i] > 9) {
			asciNmeaMsg[(*nAsciMsgLength)++] = 0x30 + averageBuffer[i] / 10;
			asciNmeaMsg[(*nAsciMsgLength)++] = 0x30 + averageBuffer[i] % 10;
		} else {
			asciNmeaMsg[(*nAsciMsgLength)++] = 0x30 + averageBuffer[i];
		}

		if (i == VERTICAL_RESOLUTION - 1) //the last element, null terminate.
			asciNmeaMsg[*nAsciMsgLength] = 0;
		else
			asciNmeaMsg[(*nAsciMsgLength)++] = ',';
	}

	//printf("end convertAverageToAsciNmea\n");
}
