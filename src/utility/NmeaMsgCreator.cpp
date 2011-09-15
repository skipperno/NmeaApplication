/*
 * NmeaMsgCreator.cpp
 *
 *  Created on: Sep 13, 2011
 *      Author: ernad
 */
#include <stdio.h>
#include <string.h>

#include "NmeaMsgCreator.h"

NmeaMsgCreator::NmeaMsgCreator() {
	// TODO Auto-generated constructor stub

}

NmeaMsgCreator::~NmeaMsgCreator() {
	// TODO Auto-generated destructor stub
}

/*
 * $--DPT,x.x,x.x,x.x*hh<CR><LF>
 * 	1. Water depth relative to the transducer [m]
 * 	2. Offset from transducer [m]
 *  3. Maximum range scale in use
 */
void NmeaMsgCreator::getDptMsgBuffer(char* buffer, float fDeapth,
		bool deapthValid, float fOffset, bool offsetValid,
		float fMaxRangeScale, bool scaleValid) {
	memset(buffer, 0, 1000);
	strcpy(buffer, "$SDDPT,");
	int nNextPos = 7;

	if (deapthValid)
		sprintf(&buffer[nNextPos], "%.1f,", fDeapth);
	else
		buffer[nNextPos] = ',';

	nNextPos = strlen(buffer);

	if (offsetValid)
		sprintf(&buffer[nNextPos], "%.1f,", fOffset);
	else
		buffer[nNextPos] = ',';

	nNextPos = strlen(buffer);

	if (scaleValid)
		sprintf(&buffer[nNextPos], "%.1f", fMaxRangeScale);

	nNextPos = strlen(buffer);

	buffer[nNextPos++] = '*';

	//TODO: checksum
	buffer[nNextPos++] = '1';
	buffer[nNextPos++] = '1';

	buffer[nNextPos] = 0;
}

/*
 * $--DBS,x.x,f,x.x,M,x.x.F*hh<CR><LF>
 * 	1. Water depth relative to the surface, in feet
 * 	2. Water depth relative to the surface, in meters
 *  3. Water depth relative to the surface, in fathoms
 */
void NmeaMsgCreator::getDbsMsgBuffer(char* buffer, float fDeapthMeter,
		bool deapthValidM, float fDeapthFeet, bool deapthValidF,
		float fDeapthFathoms, bool deapthValidFat) {
	memset(buffer, 0, 1000);
	strcpy(buffer, "$SDDBS,");
	int nNextPos = 7;

	if (deapthValidF)
		sprintf(&buffer[nNextPos], "%.1f,f,", fDeapthFeet);
	else
		strcpy(&buffer[nNextPos], ",f,");

	nNextPos = strlen(buffer);

	if (deapthValidM)
		sprintf(&buffer[nNextPos], "%.1f,M,", fDeapthMeter);
	else
		strcpy(&buffer[nNextPos], ",M,");

	nNextPos = strlen(buffer);

	if (deapthValidFat)
		sprintf(&buffer[nNextPos], "%.1f,F", fDeapthFathoms);
	else
		strcpy(&buffer[nNextPos], ",F");

	nNextPos = strlen(buffer);

	buffer[nNextPos++] = '*';

	//TODO: checksum
	buffer[nNextPos++] = '1';
	buffer[nNextPos++] = '1';

	buffer[nNextPos] = 0;
}

/*
 * $--DBT,x.x,f,x.x,M,x.x.F*hh<CR><LF>
 * 	1. Water depth relative to the transducer, in feet
 * 	2. Water depth relative to the transducer, in meters
 *  3. Water depth relative to the transducer, in fathoms
 */
void NmeaMsgCreator::getDbtMsgBuffer(char* buffer, float fDeapthMeter,
		bool deapthValidM, float fDeapthFeet, bool deapthValidF,
		float fDeapthFathoms, bool deapthValidFat) {
	memset(buffer, 0, 1000);
	strcpy(buffer, "$SDDBT,");
	int nNextPos = 7;

	if (deapthValidF)
		sprintf(&buffer[nNextPos], "%.1f,f,", fDeapthFeet);
	else
		strcpy(&buffer[nNextPos], ",f,");

	nNextPos = strlen(buffer);

	if (deapthValidM)
		sprintf(&buffer[nNextPos], "%.1f,M,", fDeapthMeter);
	else
		strcpy(&buffer[nNextPos], ",M,");

	nNextPos = strlen(buffer);

	if (deapthValidFat)
		sprintf(&buffer[nNextPos], "%.1f,F", fDeapthFathoms);
	else
		strcpy(&buffer[nNextPos], ",F");

	nNextPos = strlen(buffer);

	buffer[nNextPos++] = '*';

	//TODO: checksum
	buffer[nNextPos++] = '1';
	buffer[nNextPos++] = '1';

	buffer[nNextPos] = 0;
}

/*
 * $--DBK,x.x,f,x.x,M,x.x.F*hh<CR><LF>
 * 	1. Water depth relative to the keel, in feet
 * 	2. Water depth relative to the keel, in meters
 *  3. Water depth relative to the keel, in fathoms
 */
void NmeaMsgCreator::getDbkMsgBuffer(char* buffer, float fDeapthMeter,
		bool deapthValidM, float fDeapthFeet, bool deapthValidF,
		float fDeapthFathoms, bool deapthValidFat) {
	memset(buffer, 0, 1000);
	strcpy(buffer, "$SDDBK,");
	int nNextPos = 7;

	if (deapthValidF)
		sprintf(&buffer[nNextPos], "%.1f,f,", fDeapthFeet);
	else
		strcpy(&buffer[nNextPos], ",f,");

	nNextPos = strlen(buffer);

	if (deapthValidM)
		sprintf(&buffer[nNextPos], "%.1f,M,", fDeapthMeter);
	else
		strcpy(&buffer[nNextPos], ",M,");

	nNextPos = strlen(buffer);

	if (deapthValidFat)
		sprintf(&buffer[nNextPos], "%.1f,F", fDeapthFathoms);
	else
		strcpy(&buffer[nNextPos], ",F");

	nNextPos = strlen(buffer);

	buffer[nNextPos++] = '*';

	//TODO: checksum
	buffer[nNextPos++] = '1';
	buffer[nNextPos++] = '1';

	buffer[nNextPos] = 0;
}

/************************************************************************
 * SKIPPER Proprietary sentence
 *
 * $--PSKPDPT,x.x,f,x.x,M,x.x.F*hh<CR><LF>
 * 	1. Water depth relative to the transducer, in meters
 * 	2. Offset from transducer, meters
 *  3. Transducer location ("FWD"/"AFT"/"PORT"/"STB")
 ************************************************************************
 */
void NmeaMsgCreator::getPskpdptMsgBuffer(char* buffer, float fDeapthM,
		bool deapthValidM, float fOffsetMeter, bool offsetValidM,
		char* transdLocation, bool locationValid) {
	memset(buffer, 0, 1000);
	strcpy(buffer, "$SDPSKPDPT,");
	int nNextPos = 11;

	if (deapthValidM)
		sprintf(&buffer[nNextPos], "%.1f,", fDeapthM);
	else
		buffer[nNextPos] = ',';

	nNextPos = strlen(buffer);

	if (offsetValidM)
		sprintf(&buffer[nNextPos], "%.1f,,,,", fOffsetMeter);
	else
		strcpy(&buffer[nNextPos], ",,,,");

	nNextPos = strlen(buffer);

	if (locationValid)
		strcpy(&buffer[nNextPos], transdLocation);

	nNextPos = strlen(buffer);

	buffer[nNextPos++] = '*';

	//TODO: checksum
	buffer[nNextPos++] = '1';
	buffer[nNextPos++] = '1';

	buffer[nNextPos] = 0;
}

void NmeaMsgCreator::getXdrMsgBuffer(char* buffer, float fMeasurDataForPitch, float fMeasurmentDataForRoll) {
	memset(buffer, 0, 1000);
	strcpy(buffer, "$SDXDR,a,");
	int nNextPos = 9;

	sprintf(&buffer[nNextPos], "%.1f,D,PITCH,a", fMeasurDataForPitch);


	nNextPos = strlen(buffer);

	sprintf(&buffer[nNextPos], "%.1f,,D,ROLL", fMeasurmentDataForRoll);


	nNextPos = strlen(buffer);


	buffer[nNextPos++] = '*';

	//TODO: checksum
	buffer[nNextPos++] = '1';
	buffer[nNextPos++] = '1';

	buffer[nNextPos] = 0;
}
