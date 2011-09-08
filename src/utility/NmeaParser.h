/*
 * NmeaParser.h
 *
 *  Created on: Sep 5, 2011
 *      Author: ernad
 */

#ifndef NMEAPARSER_H_
#define NMEAPARSER_H_

#include "CircularBuffer.h"
#include "SignalGenerator.h"

class NmeaParser {
public:
	NmeaParser();
	virtual ~NmeaParser();
	void init(int nId);

	int  addChars(char* additionalBuff, int additionalLength);

private:
	int dipatchMessage();
	CircularBuffer* circularBuffer;
	int nId;
	SignalGenerator* signalGenerator;
};

#endif /* NMEAPARSER_H_ */
