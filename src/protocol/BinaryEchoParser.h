/*
 * NmeaUtility.h
 *
 *  Created on: May 11, 2011
 *      Author: Ernad Secic
 */

#ifndef BINARYECHOPARSER_H_
#define BINARYECHOPARSER_H_

class BinaryEchoParser {
public:
	BinaryEchoParser();
	virtual ~BinaryEchoParser();
	static void convertCompressedDataToAsciNmea(int nRange, char* compressedBuffer, int nCompressedLength, char* asciNmeaMsg, int * nAsciMsgLength);
	// TODO: private? Only "convertCompressedDataToAsciNmea" as public?
	static void convertCompressedDataToAverage(int nRange, char* compressedBuffer, int nCompressedLength, char* averageBuffer);
	static void convertAverageToAsciNmea(char* averageBuffer, char* asciNmeaMsg, int * nAsciMsgLength);

private:
	static void decompressData(char* compressedBuffer, int nCompressedLength, char* decompressedBuffer, int* nDecompressedLength);
};

#endif /* BINARYECHOPARSER_H_ */
