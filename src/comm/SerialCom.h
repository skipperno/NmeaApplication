/*
 * SerialCom.h
 *
 *  Created on: Sep 1, 2011
 *      Author: ernad
 */

#ifndef SERIALCOM_H_
#define SERIALCOM_H_

class SerialCom {
public:
	SerialCom();
	virtual ~SerialCom();
	int  openSerial(const char* portName, int bautRate);
	int receiveSerial(char* pBuffer, int length);
	void closeSerial();
private:
	int tty_fd;
};

#endif /* SERIALCOM_H_ */
