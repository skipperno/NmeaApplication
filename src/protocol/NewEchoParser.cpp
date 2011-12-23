/*
 * NewEchoParser.cpp
 *
 *  Created on: Jul 14, 2011
 *      Author: ernad
 */

#include "NewEchoParser.h"
#include <string.h>
#include <stdio.h>
#include "../data/Data.h"
#include "../data/ButterworthLowPassFilter.h"
#include "../data/DataProcessing.h"
#include <math.h>

int VERTICAL_RESOLUTION = 400;

NewEchoParser::NewEchoParser() {
	// TODO Auto-generated constructor stub

}

NewEchoParser::~NewEchoParser() {
	// TODO Auto-generated destructor stub
}

void NewEchoParser::convertDataToAsciNmea(int nButtom, int nRange, int nGain,
		char* inBuffer, int inLength, char* asciNmeaMsg, int * nAsciMsgLength) {
/*
		char outArray[VERTICAL_RESOLUTION + 1];
	 DataProcessing::kalmanFilter(inBuffer, 400, outArray);
//	 NewEchoParser::convertAverageToAsciNmea(nRange, nGain, outArray, asciNmeaMsg, nAsciMsgLength);
	 memcpy(inBuffer, outArray, VERTICAL_RESOLUTION);
*/
	// Low pass filter
/*	char outArray[VERTICAL_RESOLUTION + 1];
	 ButterworthLowPassFilter::test(inBuffer, 400, outArray);
	 memcpy(inBuffer, outArray, VERTICAL_RESOLUTION);*/

	// Normal
	NewEchoParser::convertAverageToAsciNmea(nButtom, nRange, nGain, inBuffer,
			asciNmeaMsg, nAsciMsgLength);
}

char NewEchoParser::calcTvg(char signal, int Tvg, float nDistance) {
	//5.f should be 30.f but signal is to strong (e.g. 30.f*log10(nDistance))
	int nTemp = (int) ((int) signal * (1.f + Tvg * 5.f * log10(nDistance)
			/ 100.f));//testTvg(Tvg, nDistance);

	if (nTemp > 255)
		return 255;
	else if (nTemp < 0)
		return 0;
	else
		return (char) nTemp;
}

/*
 * TODO: change this function and use for improving of processor performances (table for log10)
 */
float NewEchoParser::myLog10(float nDistance) {
	if (nDistance < 3)
		return 0.3f;
	if (nDistance < 10)
		return 0.8f;
	if (nDistance < 20)
		return 1.1f;
	if (nDistance < 40)
		return 1.6f; //1.6;
	if (nDistance < 100)
		return 1.9f; //1.9;
	if (nDistance < 500)
		return 2.3f; //2.3;
	if (nDistance < 1000)
		return 2.5f; //2.5;
	return 3.f; //3;
}

void NewEchoParser::convertAverageToAsciNmea(int nButtom, int nRange,
		int nGain, char* averageBuffer, char* asciNmeaMsg, int * nAsciMsgLength) {
	int nTemp;
	int nTvg;
	asciNmeaMsg[0] = '1'; // TODO: msg type
	asciNmeaMsg[1] = 0x30 + nRange;

	*nAsciMsgLength = 2;

	nGain = Data::getInstance()->getGain();
	nTvg = Data::getInstance()->getTvg();
	nRange = 50; //TODO

	if (nButtom > 9999) {
			asciNmeaMsg[(*nAsciMsgLength)++] = 0x30 + nButtom / 10000;
			asciNmeaMsg[(*nAsciMsgLength)++] = 0x30 + (nButtom % 10000) / 1000;
			asciNmeaMsg[(*nAsciMsgLength)++] = 0x30 + (nButtom % 1000) / 100;
			asciNmeaMsg[(*nAsciMsgLength)++] = 0x30 + (nButtom % 100) / 10;
			asciNmeaMsg[(*nAsciMsgLength)++] = 0x30 + nButtom % 10;
	} else if (nButtom > 999) {
		asciNmeaMsg[(*nAsciMsgLength)++] = 0x30 + nButtom / 1000;
		asciNmeaMsg[(*nAsciMsgLength)++] = 0x30 + (nButtom % 1000) / 100;
		asciNmeaMsg[(*nAsciMsgLength)++] = 0x30 + (nButtom % 100) / 10;
		asciNmeaMsg[(*nAsciMsgLength)++] = 0x30 + nButtom % 10;
	} else if (nButtom > 99) {
		asciNmeaMsg[(*nAsciMsgLength)++] = 0x30 + nButtom / 100;
		asciNmeaMsg[(*nAsciMsgLength)++] = 0x30 + (nButtom % 100) / 10;
		asciNmeaMsg[(*nAsciMsgLength)++] = 0x30 + nButtom % 10;
	} else if (nButtom > 9) {
		asciNmeaMsg[(*nAsciMsgLength)++] = 0x30 + nButtom / 10;
		asciNmeaMsg[(*nAsciMsgLength)++] = 0x30 + nButtom % 10;
	} else {
		asciNmeaMsg[(*nAsciMsgLength)++] = 0x30 + nButtom;
	}

	asciNmeaMsg[(*nAsciMsgLength)++] = ',';

	for (int i = 0; i < VERTICAL_RESOLUTION; i++) {
		nTemp = (int) averageBuffer[i] + ((int) averageBuffer[i])
				* (nGain - 50) / 100;

		if (nTemp > 255)
			nTemp = 255;

		averageBuffer[i] = calcTvg((char) nTemp, nTvg,
				((float) nRange - (float) i * nRange / VERTICAL_RESOLUTION)); //!!! Curtis-format has opposite distance order

		if (averageBuffer[i] > 99) {
			asciNmeaMsg[(*nAsciMsgLength)++] = 0x30 + averageBuffer[i] / 100;
			asciNmeaMsg[(*nAsciMsgLength)++] = 0x30 + (averageBuffer[i] % 100)
					/ 10;
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
