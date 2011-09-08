/*
 * CircularBuffer.cpp
 *
 *  Created on: Jan 18, 2010
 *      Author: ernad
 */
#include <stdio.h>
#include <string.h>
#include <malloc.h>

#include "CircularBuffer.h"
#include "ESignal.h"
#include "EByteArray.h"




CircularBuffer::CircularBuffer(int nBuffLength) {
	nStartIndex = 0;
	nLength = 0;
	nTotalLength = nBuffLength;
	chBuffer = (char*) malloc(nTotalLength);
	signalGenerator = SignalGenerator::getInstance(0);
}

CircularBuffer::~CircularBuffer() {
	free(chBuffer);
}

int CircularBuffer::addChars(char* additionalBuff, int additionalLength) {
	int freeS = getFreeSize();
	if (freeS < additionalLength)
		return -1;

	if (freeS == nTotalLength) { // empty
		memcpy(chBuffer, additionalBuff, additionalLength);
		//nEndIndex = additionalLength - 1;
	} else if (nStartIndex + nLength + additionalLength < nTotalLength) {
		memcpy(&chBuffer[nStartIndex + nLength], additionalBuff, additionalLength);
		//nEndIndex += additionalLength;
	} else {
		if(nStartIndex + nLength < nTotalLength)
			memcpy(&chBuffer[nStartIndex + nLength], additionalBuff,
					nTotalLength - (nStartIndex + nLength));

		memcpy(chBuffer, &additionalBuff[nTotalLength - (nStartIndex + nLength)],
				additionalLength - (nTotalLength - (nStartIndex + nLength)));
	}

	nLength += additionalLength;

	//printf("Add: Start: %d, length: %d\n", nStartIndex, nLength);
	return additionalLength;
}

bool CircularBuffer::isFull() {
	return (nTotalLength == nLength);
}

int CircularBuffer::getFreeSize() {
	return (nTotalLength - nLength);
}

//////////////////////////////////////////////////////////////////////////////////
// private:
//////////////////////////////////////////////////////////////////////////////////

int CircularBuffer::removeChars(int nRemoveLength) { //remove destroyed buffer
	if (nRemoveLength > nLength) {
		printf("Error: removeChars, nRemoveLength: %d, length in buffer: %d\n",
				nRemoveLength, nLength);
		return NOT_FOUND;
	}

	if (nStartIndex + nRemoveLength <= nTotalLength) { // not overflow
		nStartIndex += nRemoveLength;
		if (nStartIndex == nTotalLength)
			nStartIndex = 0;
	} else { // overflow
		nStartIndex = nRemoveLength - (nTotalLength - nStartIndex);
	}

	nLength -= nRemoveLength;

	if (nLength <= 0) {
		nStartIndex = 0;
		//nEndIndex = 0;
		nLength = 0;
	}
	//printf("REMOVE: Start: %d, length: %d\n", nStartIndex, nLength);
	return nRemoveLength;
}

int CircularBuffer::getChars(int msgLength, char* destBuff) {
	if (msgLength > nLength) {
		//printf("Error getChars. msgLength= %d, totLeng: %d\n",msgLength, nLength);
		return 0;
	}
	if (nStartIndex + msgLength <= nTotalLength) {
		memcpy(destBuff, &chBuffer[nStartIndex], msgLength);
		//nStartIndex += msgLength;
	} else { // overflow
		memcpy(destBuff, &chBuffer[nStartIndex], nTotalLength - nStartIndex);
		memcpy(&destBuff[nTotalLength - nStartIndex], chBuffer, msgLength - (nTotalLength - nStartIndex));
	}
	//printf("Get %d chars\n", msgLength);
	removeChars(msgLength);
	//nLength -= msgLength;
	return msgLength;
}

// return 1 if first char in buffer is "searchChar", 2 if second ...
int CircularBuffer::getMsgStartPos(char searchChar) {
	if (nStartIndex + nLength > nTotalLength) { // overflow
		for (int i = nStartIndex; i < nTotalLength; i++) {
			if (chBuffer[i] == searchChar)
				return (i - nStartIndex + 1);
		}

		for (int i = 0; i < nLength - (nTotalLength - nStartIndex); i++) {
			if (chBuffer[i] == searchChar)
				return (nTotalLength - nStartIndex + i + 1);
		}
	} else {
		for (int i = nStartIndex; i < (nStartIndex + nLength); i++) {
			if (chBuffer[i] == searchChar)
				return (i - nStartIndex + 1);
		}
	}

	return NOT_FOUND;
}

/*
 * Search index of "searchChar". !!! If "unwantedChar" found before "searchChar", negative index of "unwantedChar" is returned.
 * Returned index of found "searchChar" or -1 if not found.
 */
int CircularBuffer::getMsgEndPos(char searchChar, char unwantedChar) {
	if (nStartIndex + nLength > nTotalLength) { // overflow
		for (int i = nStartIndex + 1; i < nTotalLength; i++) {
			if (chBuffer[i] == unwantedChar) {
				printf("Found unwanted * on pos: %d\n", (i - nStartIndex + 1));
				return (i - nStartIndex + 1) * (-1); //ERROR: found unwanted character. Return negative index of unwanted ch.
			}
			if (chBuffer[i] == searchChar) {
				//if (i - nStartIndex + 1 <= nLength - 2) { // check sum also received
					return (i - nStartIndex + 1);
				/*} else {
					return NOT_FOUND; // wait on check sum
				}*/
			}
		}

		for (int i = 0; i < nLength - (nTotalLength - nStartIndex); i++) {
			if (chBuffer[i] == unwantedChar) {
				printf("2. Found unwanted * on pos: %d\n", (nTotalLength - nStartIndex + i + 1));
				return (nTotalLength - nStartIndex + i + 1) * (-1); //ERROR: found unwanted character. Return negative index of unwanted ch.
			}

			if (chBuffer[i] == searchChar)
				return (nTotalLength - nStartIndex + i + 1);
		}
	} else { // not overflow
		for (int i = nStartIndex + 1; i < (nStartIndex + nLength); i++) {
			if (chBuffer[i] == unwantedChar) {
				printf("3. Found unwanted * on pos: %d\n", (i - nStartIndex + 1));
				return (i - nStartIndex + 1) * (-1); //ERROR: found unwanted character. Return negative index of unwanted ch.
			}

			if (chBuffer[i] == searchChar)
				return (i - nStartIndex + 1);
		}
	}

	return NOT_FOUND;
}

// return 1 if first char in buffer is "searchChar", 2 if second ...
bool CircularBuffer::isThisCharOnPosition(char searchChar, int nPosition) {
	if (nLength < nPosition) {
		return false;
	}

	if (nStartIndex + nPosition > nTotalLength) { // overflow
		return (searchChar == chBuffer[nPosition - (nTotalLength - nStartIndex)] - 1);
	} else {
		return (searchChar == chBuffer[nStartIndex + nPosition]);
	}
}

int CircularBuffer::getBufferSize() {
	return nLength;
}
/**
 * !!! If 2 "startChars" found, all chars before second "startChar" are deleted.
 */

