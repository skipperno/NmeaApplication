/*
 * NmeaUtility.cpp
 *
 *  Created on: May 11, 2011
 *      Author: Ernad Secic
 */

#include "NmeaUtility.h"
#include <string.h>
#include <stdio.h>

#define AVERAGED_RESOLUTION 400


NmeaUtility::NmeaUtility() {
	// TODO Auto-generated constructor stub

}

NmeaUtility::~NmeaUtility() {
	// TODO Auto-generated destructor stub
}

void NmeaUtility::convertCompressedDataToAsciNmea(char* compressedBuffer, int nCompressedLength, char* asciNmeaMsg, int * nAsciMsgLength) {
	char averageBuffer[AVERAGED_RESOLUTION];
	convertCompressedDataToAverage(compressedBuffer, nCompressedLength, averageBuffer);

	convertAverageToAsciNmea(averageBuffer, asciNmeaMsg, nAsciMsgLength);
}

void NmeaUtility::convertCompressedDataToAverage(char* compressedBuffer, int nCompressedLength, char* averageBuffer) {
	//printf("start convertCompressedDataToAverage\n");
	char decomprBuffer[6000]; //TODO: 6000 or more?
	int nDecompressedLength = 0;

	decompressData(compressedBuffer, nCompressedLength, decomprBuffer, &nDecompressedLength);

	unsigned int nCountPerMeassurment;
	unsigned int nSum = 0;

	if (nDecompressedLength <= 0) {
		printf("!!!!!!!!!!!!!!!!!!! received length <= 0\n");
		return;
	}

	nCountPerMeassurment = (unsigned int)nDecompressedLength / AVERAGED_RESOLUTION;

	for (int i = 0; i < AVERAGED_RESOLUTION; i++) {
		nSum = 0;
		for (int j = 0; j < (int)nCountPerMeassurment; j++) {
			nSum += decomprBuffer[i * nCountPerMeassurment + j];
		}

		averageBuffer[i] = (char)(nSum / nCountPerMeassurment);
	}
	//printf("end convertCompressedDataToAverage\n");
}


void NmeaUtility::convertAverageToAsciNmea(char* averageBuffer, char* asciNmeaMsg, int * nAsciMsgLength) {
	char nmeaStart[] = {"$PSKPES,400,"};
	strcpy(asciNmeaMsg, nmeaStart);
	*nAsciMsgLength = 12;
	//printf("start convertAverageToAsciNmea\n");

	for (int i = 0; i < AVERAGED_RESOLUTION; i++) {
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

		if (i == AVERAGED_RESOLUTION - 1) //the last element, null terminate.
			asciNmeaMsg[*nAsciMsgLength] = 0;
		else
			asciNmeaMsg[(*nAsciMsgLength)++] = ',';
	}

	//printf("end convertAverageToAsciNmea\n");
}

void NmeaUtility::decompressData(char* compressedBuffer, int nCompressedLength, char* decompressedBuffer, int* nDecompressedLength) {
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
