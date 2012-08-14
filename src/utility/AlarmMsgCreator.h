/*
 * AlarmMsgCreator.h
 *
 *  Created on: Feb 27, 2012
 *      Author: ernad
 */

#ifndef ALARMMSGCREATOR_H_
#define ALARMMSGCREATOR_H_

class AlarmMsgCreator {
public:
	AlarmMsgCreator();
	virtual ~AlarmMsgCreator();

	static void getAlarmMsgBuffer(char* buffer, int nId, float deapth, bool isAlarm, bool isConfirmed);
};

#endif /* ALARMMSGCREATOR_H_ */
