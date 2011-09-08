/*
 * CurtisFormatParser.cpp
 *
 *  Created on: Sep 5, 2011
 *      Author: ernad
 */

#include "CurtisFormatParser.h"

#include "CircularBuffer.h"
#include "ESignal.h"
#include "EByteArray.h"

CurtisFormatParser::CurtisFormatParser() {
	signalGenerator = SignalGenerator::getInstance(0);
	circularBuffer = new CircularBuffer(3000);
	this->nId = 0;
}

CurtisFormatParser::~CurtisFormatParser() {
	// TODO Auto-generated destructor stub
}

void CurtisFormatParser::init(int nId) {
	this->nId = nId;
}

int CurtisFormatParser::addChars(char* additionalBuff, int additionalLength) {
	circularBuffer->addChars(additionalBuff, additionalLength);
	return dipatchMessage();
}

int CurtisFormatParser::dipatchMessage() {
	if (circularBuffer->getBufferSize() < 514)
		return 0;

	int nStartCharPos = circularBuffer->getMsgStartPos('$');
	int nMsgSize = -1;

	if (nStartCharPos == NOT_FOUND) // not found
		return 0; // not completed yet
	else if (nStartCharPos > 1) { // clear garbage buffer in the beginning
		//printf("remove: %d\n", (nStartCharPos - 1));
		circularBuffer->removeChars(nStartCharPos - 1);
		nStartCharPos = 1;
	}

	if (circularBuffer->isThisCharOnPosition('*', 513)) {
		EByteArray *eByteArray = new EByteArray();
		eByteArray->resize(514);

		if (circularBuffer->getChars(514, eByteArray->data())) {
			signalGenerator->addSignal(new ESignal(this->nId, eByteArray));

			return nMsgSize;
		} else {
			return 0;
		}
	} else {
		circularBuffer->removeChars(1); // TODO: optimize. Remove first "$". Better: remove all chars until next "$"
	}
	/*
	 int nEndCharPos = circularBuffer->getMsgEndPos('*', '$');

	 if (nEndCharPos > 1) {
	 nMsgSize = nEndCharPos;
	 EByteArray *eByteArray = new EByteArray();
	 eByteArray->resize(nMsgSize);

	 if (circularBuffer->getChars(nMsgSize, eByteArray->data())) {
	 //EByteArray *byteArray = new EByteArray();
	 //byteArray->append(destBuff, nMsgSize);
	 signalGenerator->addSignal(new ESignal(this->nId, eByteArray));

	 return nMsgSize;
	 } else
	 return 0;
	 } else if (nEndCharPos != NOT_FOUND) { // found new "startChar" before "endChar". Remove destroyed buffer.
	 //printf("!!! remove: %d\n", (nEndCharPos * (-1)));
	 circularBuffer->removeChars(nEndCharPos * (-1));
	 return -1; // wrong, try again
	 }
	 */
	return 0; // not completed yet
}
