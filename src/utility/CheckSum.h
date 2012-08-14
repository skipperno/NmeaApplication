/*
 * CheckSum.h
 *
 *  Created on: Feb 13, 2012
 *      Author: ernad
 */

#ifndef CHECKSUM_H_
#define CHECKSUM_H_

class CheckSum {
public:
	CheckSum();
	virtual ~CheckSum();

	static unsigned char calculate8bitCheckSum(const char * buff, int nLen);
};

#endif /* CHECKSUM_H_ */
