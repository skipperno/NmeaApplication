/*
 * SysTime.cpp
 *
 *  Created on: Aug 30, 2011
 *      Author: ernad
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h> //#include <sys/time.h>
#include <string.h>

#include "SysTime.h"

SysTime::SysTime() {
	// TODO Auto-generated constructor stub

}

SysTime::~SysTime() {
	// TODO Auto-generated destructor stub
}

void SysTime::sysTime_set(int nYear, int nMonth, int nDay, int nHour, int nMin, int nSec) {
	struct tm newTime;
	time_t currentTime;

	newTime.tm_year = nYear - 1900;
	newTime.tm_mon = nMonth - 1;
	newTime.tm_mday = nDay;
	newTime.tm_hour = nHour;
	newTime.tm_min = nMin;
	newTime.tm_sec = nSec;
	newTime.tm_isdst = -1;
	fprintf(stderr, "saving time. Year: %.4d M:%.2d D:%.2d", nYear, nMonth, nDay);
	//currentTime = time(NULL) ;
	//currentTime += 365*24*60*60*40;
	currentTime = mktime(&newTime);

	stime(&currentTime);

	system ("hwclock -w"); // shell command, writing to hardware clock
	// hvis ikke har den, mister tid etter restart
}

void SysTime::sysTime_get(GW_TIME * timeStruct) {
	time_t currentTime;
	struct tm *timeptr;
	//char line[MAX_LINE];

	currentTime = time((time_t *) NULL);
	timeptr = localtime(&currentTime);

	timeStruct->gwNewDate.year = timeptr->tm_year + 1900;
	timeStruct->gwNewDate.month = timeptr->tm_mon + 1;
	timeStruct->gwNewDate.day = timeptr->tm_mday;

	timeStruct->gwNewTime.hour = timeptr->tm_hour;
	timeStruct->gwNewTime.min = timeptr->tm_min;
	timeStruct->gwNewTime.sec = timeptr->tm_sec;
}

/*
 *
/////////////////////////////////////////////////////
// currDate format: 24.03.2010 // 11 char includ. nullterm.
// currTime format: 11:03:56   //  9 char includ. nullterm.
/////////////////////////////////////////////////////
int sysTime_toString(char* currDate, char* currTime) {
	time_t currentTime;
	struct tm *timeptr;
	//char line[MAX_LINE];

	currentTime = time((time_t *) NULL);
	timeptr = localtime(&currentTime);

	snprintf(currDate, 25, "%.2d.%.2d.%.4d", timeptr->tm_mday, timeptr->tm_mon
			+ 1, timeptr->tm_year + 1900);

	snprintf(currTime, 25, "%.2d:%.2d:%.2d", timeptr->tm_hour, timeptr->tm_min,
			timeptr->tm_sec);

	return 1;
}

int sysTime_toString2(char* currDate, char* currTime) {
	time_t currentTime;
	struct tm *timeptr;
	//char line[MAX_LINE];

	currentTime = time((time_t *) NULL);
	timeptr = localtime(&currentTime);
	snprintf(currDate, 25, "%.2d_%.2d_%.4d", timeptr->tm_mday, timeptr->tm_mon
			+ 1, timeptr->tm_year + 1900);

	snprintf(currTime, 25, "%.2d_%.2d_%.2d", timeptr->tm_hour, timeptr->tm_min,
			timeptr->tm_sec);

	return 1;
}

int sysTime_toString3(char* currDate, char* currTime) {
	time_t currentTime;
	struct tm *timeptr;
	//char line[MAX_LINE];

	currentTime = time((time_t *) NULL);
	timeptr = localtime(&currentTime);
	snprintf(currDate, 25, "%.4d_%.2d_%.2d", timeptr->tm_year + 1900, timeptr->tm_mon
			+ 1, timeptr->tm_mday);

	snprintf(currTime, 25, "%.2d_%.2d_%.2d", timeptr->tm_hour, timeptr->tm_min,
			timeptr->tm_sec);

	return 1;
}
 */

