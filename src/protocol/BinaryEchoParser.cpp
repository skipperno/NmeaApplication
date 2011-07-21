/*
 * NmeaUtility.cpp
 *
 *  Created on: May 11, 2011
 *      Author: Ernad Secic
 */

#include "BinaryEchoParser.h"
#include <string.h>
#include <stdio.h>

#define VERT_RESOLUTION 400


BinaryEchoParser::BinaryEchoParser() {
	// TODO Auto-generated constructor stub

}

BinaryEchoParser::~BinaryEchoParser() {
	// TODO Auto-generated destructor stub
}

void BinaryEchoParser::convertCompressedDataToAsciNmea(int nRange, char* compressedBuffer, int nCompressedLength, char* asciNmeaMsg, int * nAsciMsgLength) {
	char averageBuffer[VERT_RESOLUTION + 2]; // 2 for header (1- type, 2-range)
	convertCompressedDataToAverage(nRange, compressedBuffer, nCompressedLength, averageBuffer);

	convertAverageToAsciNmea(nRange, averageBuffer, asciNmeaMsg, nAsciMsgLength);
}

void BinaryEchoParser::convertCompressedDataToAverage(int nRange, char* compressedBuffer, int nCompressedLength, char* averageBuffer) {
	//printf("start convertCompressedDataToAverage\n");
	char decomprBuffer[6000]; //TODO: 6000 or more?
	int nDecompressedLength = 0;

	decompressData(compressedBuffer, nCompressedLength, decomprBuffer, &nDecompressedLength);
// printf("decompressed len: %d\n", nDecompressedLength);
	unsigned int nCountPerMeassurment;
	unsigned int nSum = 0;

	if (nDecompressedLength <= 0) {
		printf("!!!!!!!!!!!!!!!!!!! received length <= 0\n");
		return;
	}

	int rangeLength[] = {10, 50, 100, 500, 1000, 1600}; //TODO: wrong place for this array

	// !!! Here is assuming that data from simulator applies to depth of 1600m.
	nCountPerMeassurment = ((unsigned int)nDecompressedLength - (unsigned int)nDecompressedLength*rangeLength[nRange]/1600)/ VERT_RESOLUTION;



	for (int i = 0; i < VERT_RESOLUTION; i++) {
		nSum = 0;
		for (int j = 0; j < (int)nCountPerMeassurment; j++) {
			nSum += decomprBuffer[i * nCountPerMeassurment + j];
		}


		averageBuffer[i] = (char)(nSum / nCountPerMeassurment);
	}
	//printf("end convertCompressedDataToAverage\n");
}


void BinaryEchoParser::convertAverageToAsciNmea(int nRange, char* averageBuffer, char* asciNmeaMsg, int * nAsciMsgLength) {
	/*char nmeaStart[] = {"$PSKPES,400,"};
	strcpy(asciNmeaMsg, nmeaStart);
	*nAsciMsgLength = 12;*/
	//printf("start convertAverageToAsciNmea\n");

	//Data starts from byte No. 2. (averageBuffer[0] = msgType, averageBuffer[1] = range)
	asciNmeaMsg[0] = '1'; // TODO: msg type
	asciNmeaMsg[1] = 0x30 + nRange;

	*nAsciMsgLength = 2;

	for (int i = 0; i < VERT_RESOLUTION; i++) {
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

		if (i == VERT_RESOLUTION - 1) //the last element, null terminate.
			asciNmeaMsg[*nAsciMsgLength] = 0;
		else
			asciNmeaMsg[(*nAsciMsgLength)++] = ',';
	}

	//printf("end convertAverageToAsciNmea\n");
}

void BinaryEchoParser::decompressData(char* compressedBuffer, int nCompressedLength, char* decompressedBuffer, int* nDecompressedLength) {
	//printf("start decompressData\n");
	for (int i = 0; i < nCompressedLength; i++) {
		if (compressedBuffer[i] != 0) {
			decompressedBuffer[(*nDecompressedLength)++] = compressedBuffer[i];
		} else { // get "number of zero values"
			for (int k = 0; k < compressedBuffer[i+1]; k++) {
				decompressedBuffer[(*nDecompressedLength)++] = 0;
			}
			i++;
		}
	}

	//printf("end decompressData\n");
}
