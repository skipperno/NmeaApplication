/*
 * Mock.cpp
 *
 *  Created on: 3. mai 2011
 *      Author: Ernad Secic
 */

#include <stdio.h>
#include <string.h>

#include "Mock.h"

int aa;
int nTest = 0;
char testArray[] =  "1,3,8,20,20,25,34,56,66,66,32,28,50,70,90,120,150,160,220,255,\
					230,240,220,190,110,90,140,120,100,30,\
					90,90,80,89,120,150,29,88,99,120,\
					160,189,240,220,120,12,90,80,80,90,\
					1, 3, 8,20,20,25,34,56,66,66,\
					32,28,50,70,90,120,150,160,220,255,\
					230,240,220,190,110,90,140,120,100,30,\
					90,90,80,89,120,150,29,88,99,120,\
					160,189,240,220,120,10,90,80,80,90,\
					160,189,240,220,120,10,90,80,80,90,\
					90,90,80,89,120,150,29,88,99,120,\
					230,240,220,190,110,90,140,120,100,30,\
					32,28,50,70,90,120,150,160,220,255,\
					1, 3, 8,20,20,25,34,56,66,66,\
					160,189,240,220,120,10,90,80,80,90,\
					90,90,80,89,120,150,29,88,99,120,\
					230,240,220,190,110,90,140,120,100,30,\
					32,28,50,70,90,120,150,160,220,255,\
					1,3,8,20,20,25,34,56,66,66,\
					1,3,8,20,20,25,34,56,66,66,\
					1,3,8,20,20,25,34,56,66,66,\
					1,3,8,20,20,25,34,56,66,66,\
					1,3,8,20,20,25,34,56,66,66,\
					1,3,8,20,20,25,34,56,66,66,\
					1,3,8,20,20,25,12";

Mock::Mock() {
	// TODO Auto-generated constructor stub

}

Mock::~Mock() {
	// TODO Auto-generated destructor stub
}

int Mock::getNumber() {
	aa++;
	return aa;
}

void Mock::getString(char * chBuff) {
	sprintf(chBuff, "%d $SDMA, 0, 1, 222, 3.5, 335, 1023 $SDMA $SDMA, 0, 1, 222, 3.5, 335, 1023 $SDMA, 0, 1, 222, 3.5, 335, 1023, 0, 1, 222, 3.5, 335, 1023 $SDMA, 0, 1, 222, 3.5, 335, 1023 $SDMA, 0, 1, 222, 3.5, 335, 1023", aa);
	aa ++;
}

void Mock::getByteString(char * chBuff) {
	int nLen = strlen(testArray);
	for (int i = 0; i < nLen; i++) {
		chBuff[i] = testArray[i];
		//sprintf(chBuff++, "%c", testArray[i]);
		//if (testArray[i] > 99)
			//chBuff
	}
	if (nTest == 0) {
		chBuff[0]='1';
		nTest = 1;
	} else {
		nTest = 0;
		chBuff[0]='9';
	}
	chBuff[nLen] = 0;
}
