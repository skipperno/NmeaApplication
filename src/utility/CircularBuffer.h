/*
 * CircularBuffer.h
 *
 *  Created on: Jan 18, 2010
 *      Author: ernad
 */

#ifndef CIRCULARBUFFER_H_
#define CIRCULARBUFFER_H_

#include "SignalGenerator.h"

#define NOT_FOUND -100000 //TODO: min int

class CircularBuffer {
public:
	CircularBuffer(int nBuffLength);
	virtual ~CircularBuffer();

	int addChars(char* additionalBuff, int additionalLength);
	//int getMessage(char startChar, char endChar, char* destBuff);
	bool isFull();
	int getFreeSize();
	int getBufferSize();

	int removeChars(int nRemoveLength);
	int getChars(int removingLength, char* destBuff);
	int getMsgStartPos(char searchChar);
	int getMsgEndPos(char searchChar, char unwantedChar);
	bool isThisCharOnPosition(char searchChar, int nPosition);

private:

	int nStartIndex;
	int nLength;
	int nTotalLength;

	char* chBuffer;
	SignalGenerator* signalGenerator;
};

#endif /* CIRCULARBUFFER_H_ */
