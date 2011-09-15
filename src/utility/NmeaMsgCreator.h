/*
 * NmeaMsgCreator.h
 *
 *  Created on: Sep 13, 2011
 *      Author: ernad
 */

#ifndef NMEAMSGCREATOR_H_
#define NMEAMSGCREATOR_H_

class NmeaMsgCreator {
public:
	NmeaMsgCreator();
	virtual ~NmeaMsgCreator();

	static void getDptMsgBuffer(char* buffer, float fDeapth, bool deapthValid,
				float fOffset, bool offsetValid, float fMaxRangeScale, bool scaleValid);
	static void getDbsMsgBuffer(char* buffer, float fDeapthMeter, bool deapthValidM, float fDeapthFeet, bool deapthValidF,
			float fDeapthFathoms, bool deapthValidFat);
	static void getDbtMsgBuffer(char* buffer, float fDeapthMeter, bool deapthValidM, float fDeapthFeet, bool deapthValidF,
			float fDeapthFathoms, bool deapthValidFat);
	static void getDbkMsgBuffer(char* buffer, float fDeapthMeter, bool deapthValidM, float fDeapthFeet, bool deapthValidF,
			float fDeapthFathoms, bool deapthValidFat);
	static void getPskpdptMsgBuffer(char* buffer, float fDeapthM, bool deapthValidM,
			float fOffsetMeter, bool offsetValidM, char* transdLocation, bool locationValid);
	static void getXdrMsgBuffer(char* buffer, float fMeasurDataForPitch, float fMeasurmentDataForRoll);
};

#endif /* NMEAMSGCREATOR_H_ */
