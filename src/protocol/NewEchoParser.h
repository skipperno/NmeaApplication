/*
 * NewEchoParser.h
 *
 *  Created on: Jul 14, 2011
 *      Author: ernad
 */

#ifndef NEWECHOPARSER_H_
#define NEWECHOPARSER_H_

class NewEchoParser {
public:
	NewEchoParser();
	virtual ~NewEchoParser();
	static void convertDataToAsciNmea(int nRange, char* inBuffer, int inLength, char* asciNmeaMsg, int * nAsciMsgLength);
private:
	static void convertAverageToAsciNmea(int nRange, char* averageBuffer, char* asciNmeaMsg, int * nAsciMsgLength);
};

#endif /* NEWECHOPARSER_H_ */
