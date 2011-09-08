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
	static void sysTime_get(GW_TIME * timeStruct);
};

#endif /* SYSTIME_H_ */
