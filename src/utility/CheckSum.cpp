/*
 * CheckSum.cpp
 *
 *  Created on: Feb 13, 2012
 *      Author: ernad
 */

#include "CheckSum.h"

CheckSum::CheckSum() {
	// TODO Auto-generated constructor stub

}

CheckSum::~CheckSum() {
	// TODO Auto-generated destructor stub
}

unsigned char CheckSum::calculate8bitCheckSum(const char * buff, int nLen){
	unsigned char ret = 0;

	for (int i = 0; i< nLen; i++) {
		ret^=buff[i];
	}
	return ret;
}
