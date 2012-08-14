/*
 * SysTime.h
 *
 *  Created on: Aug 30, 2011
 *      Author: ernad
 */

#ifndef SYSTIME_H_
#define SYSTIME_H_


typedef struct {
	int hour;
	int min;
	int sec;
} GW_NEWTIME;

typedef struct {
	int day;
	int month;
	int year;
} GW_NEWDATE;

typedef struct {
	char n[30]; // gateway name
	GW_NEWTIME gwNewTime;
	GW_NEWDATE gwNewDate;
} GW_TIME;

class SysTime {
public:
	SysTime();
	virtual ~SysTime();

	static void sysTime_set(int nYear, int nMonth, int nDay, int nHour, int nMin, int nSec);
	static int sysTime_get(GW_TIME * timeStruct);
	static int sysTime_toString(char* currDate, char* currTime);
	static int sysTime_toString2(char* currDateAndTime);
	static int sysTime_toString3(char* currDate, char* currTime);
	static int sysDate_toStringNotSeparator(char* currDate);
	static int minutSecondToString(char* currMinAndSecond);
	static int getDay();
};

#endif /* SYSTIME_H_ */
