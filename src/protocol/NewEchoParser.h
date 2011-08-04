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
	static void convertDataToAsciNmea(int nButtom, int nRange, int nGain, char* inBuffer, int inLength, char* asciNmeaMsg, int * nAsciMsgLength);
private:
	static void convertAverageToAsciNmea(int nButtom, int nRange, int nGain, char* averageBuffer, char* asciNmeaMsg, int * nAsciMsgLength);
	static char calcTvg(char signal, int Tvg, float nDistance);
	static float myLog10(float nDistance);
};

#endif /* NEWECHOPARSER_H_ */
