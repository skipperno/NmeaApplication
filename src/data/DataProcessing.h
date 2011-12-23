/*
 * DataProcessing.h
 *
 *  Created on: Aug 3, 2011
 *      Author: ernad
 */

#ifndef DATAPROCESSING_H_
#define DATAPROCESSING_H_

class DataProcessing {
public:
	DataProcessing();
	virtual ~DataProcessing();

	static void kalmanFilter(char* inArray, int dataLength, char*outArray);
	static int bottomDetection(char* inArray, int dataLength);

private:
	static int getMaxDiff(unsigned char* inArray, int arrayLenght);
	static void getSegmentsArray(char* inArray, int dataLength, int segmentsCount, int segmLeng, int* segmArray);
	static int getTopSegment(int* inArray, int dataLength);

	static int getBottomStartIndex(unsigned char* inArray, int arrayLenght, int segmentIndex, int segmentLength);
	static int getTopInsideSegment(unsigned char* inArray, int arrayLenght);
	static int getIncreasingStart(unsigned char* inArray, int arrayLenght, int topIndex, int maxSearchLength);
	static void getMaxMinInsideSegment(unsigned char* inArray, int arrayLenght, int * nMinIndex, int * nMaxIndex);
};

#endif /* DATAPROCESSING_H_ */
