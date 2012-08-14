/*
 * AlarmMsgCreator.cpp
 *
 *  Created on: Feb 27, 2012
 *      Author: ernad
 */

#include "AlarmMsgCreator.h"
#include "CheckSum.h"

#include <stdio.h>
#include <string.h>

const char ALARM_NMEA_MSG_PREF[] = {"$VDALR,"};
const char ALARM_NMEA_MSG[] = {"hello world"};

AlarmMsgCreator::AlarmMsgCreator() {
	// TODO Auto-generated constructor stub

}

AlarmMsgCreator::~AlarmMsgCreator() {
	// TODO Auto-generated destructor stub
}

void AlarmMsgCreator::getAlarmMsgBuffer(char* buffer, int nId, float depth, bool isAlarm, bool isConfirmed) {
	//memset(buffer, 0, 1000);
	strcpy(buffer, ALARM_NMEA_MSG_PREF);

	int nNextPos = strlen(ALARM_NMEA_MSG_PREF);

	sprintf(&buffer[nNextPos], "%.4f,", depth);
	nNextPos += 4;
	buffer[nNextPos++] = ',';
	sprintf(&buffer[nNextPos], "%.3d,", nId);
	nNextPos += 3;
	buffer[nNextPos++] = ',';

	if (isAlarm)
		buffer[nNextPos++] = 'A';
	else
		buffer[nNextPos++] = 'V';

	buffer[nNextPos++] = ',';

	if (isConfirmed)
		buffer[nNextPos++] = 'A';
	else
		buffer[nNextPos++] = 'V';

	buffer[nNextPos++] = ',';

	sprintf(&buffer[nNextPos], "%s", ALARM_NMEA_MSG);
	nNextPos += strlen(ALARM_NMEA_MSG);

	unsigned char cs = CheckSum::calculate8bitCheckSum(buffer, nNextPos);
	buffer[nNextPos++] = '*';
	sprintf(&buffer[nNextPos], "%.2X", cs);
}
