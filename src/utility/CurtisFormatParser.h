/*
 * CurtisFormatParser.h
 *
 *  Created on: Sep 5, 2011
 *      Author: ernad
 */

#ifndef CURTISFORMATPARSER_H_
#define CURTISFORMATPARSER_H_

#include "CircularBuffer.h"
#include "SignalGenerator.h"

class CurtisFormatParser {
public:
	CurtisFormatParser();
	virtual ~CurtisFormatParser();
	void init(int nId);

		int  addChars(char* additionalBuff, int additionalLength);

	private:
		int dipatchMessage();
		CircularBuffer* circularBuffer;
		int nId;
		SignalGenerator* signalGenerator;
};

#endif /* CURTISFORMATPARSER_H_ */
