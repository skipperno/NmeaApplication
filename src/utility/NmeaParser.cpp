/*
 * NmeaParser.cpp
 *
 *  Created on: Sep 5, 2011
 *      Author: ernad
 */

#include "NmeaParser.h"
#include "CircularBuffer.h"
#include "ESignal.h"
#include "EByteArray.h"
#include "NmeaMsgParser.h"

NmeaParser::NmeaParser() {
	signalGenerator = SignalGenerator::getInstance(0);
	circularBuffer = new CircularBuffer(3000);
	this->nId = 0;
}

NmeaParser::~NmeaParser() {
	// TODO Auto-generated destructor stub
}

void NmeaParser::init(int nId) {
	this->nId = nId;
}

int  NmeaParser::addChars(char* additionalBuff, int additionalLength){
	circularBuffer->addChars(additionalBuff, additionalLength);
	return dipatchMessage();
}

int NmeaParser::dipatchMessage() {
	int nStartCharPos = circularBuffer->getMsgStartPos('$');
	int nMsgSize = -1;

	if (nStartCharPos == NOT_FOUND) // not found
		return 0; // not completed yet
	else if (nStartCharPos > 1) { // clear garbage buffer in the beginning
		//printf("remove: %d\n", (nStartCharPos - 1));
		circularBuffer->removeChars(nStartCharPos - 1);
		nStartCharPos = 1;
	}
	int nEndCharPos = circularBuffer->getMsgEndPos('*', '$');

	if (nEndCharPos > 1) {
		nMsgSize = nEndCharPos + 2; // 2 for check sum
		EByteArray *eByteArray = new EByteArray();
		eByteArray->resize(nMsgSize);

		if (circularBuffer->getChars(nMsgSize, eByteArray->data())) {
			NMEA_TALKER_ID talkerId = NmeaMsgParser::GetTalkerIdentifier(eByteArray->data());
			if (talkerId == GP) {
				NMEA_MSG_TYPE msgType = NmeaMsgParser::GetGpsMsgType(eByteArray->data());
				if (msgType == GPGGA) {
					NmeaMsgParser::ParseGPGGA(eByteArray->data());
					//signalGenerator->addSignal(new ESignal(this->nId, eByteArray));
				}
			} else if (talkerId == WI) {
				NMEA_MSG_TYPE msgType = NmeaMsgParser::GetWiMsgType(eByteArray->data());
				if (msgType == WIMDA) {
					NmeaMsgParser::ParseWIMDA(eByteArray->data());
					//signalGenerator->addSignal(new ESignal(this->nId, eByteArray));
				}
			}
			signalGenerator->addSignal(new ESignal(this->nId, eByteArray));
			return nMsgSize;
		} else
			return 0;
	} else if (nEndCharPos != NOT_FOUND) { // found new "startChar" before "endChar". Remove destroyed buffer.
		//printf("!!! remove: %d\n", (nEndCharPos * (-1)));
		circularBuffer->removeChars(nEndCharPos * (-1));
		return -1; // wrong, garbage removed, try again
	}

	return 0; // not completed yet
}
