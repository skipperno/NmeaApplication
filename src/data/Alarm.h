/*
 * Alarm.h
 *
 *  Created on: Jan 23, 2012
 *      Author: ernad
 */

#ifndef ALARM_H_
#define ALARM_H_

class Alarm {
public:
	Alarm();
	virtual ~Alarm();

	static int initAlarm();
	static int updateAlarmState(int nBottom);
	static void confirmAlarm();

	static bool isAlarmState();
	static bool isConfirmed();

	static void setAlarmSenderId(int alarmId);
	static int  getAlarmSenderId();
};

#endif /* ALARM_H_ */
