/*
 * NmeaUtility.h
 *
 *  Created on: May 11, 2011
 *      Author: Ernad Secic
 */

#ifndef NMEAUTILITY_H_
#define NMEAUTILITY_H_

class NmeaUtility {
public:
	NmeaUtility();
	virtual ~NmeaUtility();
	static void convertCompressedDataToAsciNmea(char* compressedBuffer, int nCompressedLength, char* asciNmeaMsg, int * nAsciMsgLength);
	// TODO: private? Only "convertCompressedDataToAsciNmea" as public?
	static void convertCompressedDataToAverage(char* compressedBuffer, int nCompressedLength, char* averageBuffer);
	static void convertAverageToAsciNmea(char* averageBuffer, char* asciNmeaMsg, int * nAsciMsgLength);

private:
	static void decompressData(char* compressedBuffer, int nCompressedLength, char* decompressedBuffer, int* nDecompressedLength);
};

#endif /* NMEAUTILITY_H_ */
