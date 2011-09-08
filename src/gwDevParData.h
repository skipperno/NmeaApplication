/*
 * gwDevPar.h
 *
 *  Created on: 6. apr. 2010
 *      Author: Ernad
 */

#ifndef GWDEVPARDATA_H_
#define GWDEVPARDATA_H_

#define GW_NEW_YEAR_ALIAS 						"gw_year"
#define GW_NEW_MONTH_ALIAS 						"gw_month"
#define GW_NEW_DAY_ALIAS 						"gw_day"
#define GW_NEW_HOUR_ALIAS 						"gw_hour"
#define GW_NEW_MIN_ALIAS 						"gw_min"
#define GW_NEW_SEC_ALIAS 						"gw_sec"

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

#endif /* GWDEVPAR_H_ */
