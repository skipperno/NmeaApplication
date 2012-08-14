/*
 * SerialCom.h
 *
 *  Created on: Sep 1, 2011
 *      Author: ernad
 */

#ifndef SERIALCOM_H_
#define SERIALCOM_H_

#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

class SerialCom {
public:
	SerialCom();
	virtual ~SerialCom();
	int  openSerial(const char* portName, int bautRate);
	int receiveSerial(char* pBuffer, int length);
	int sendSerial(const char* pBuffer, int length);
	void closeSerial();
	static int getBaudByIndex(int nIndex);
private:
	int tty_fd;
	int baudRate;
	char portName[10];

	// Initialize file descriptor sets
	fd_set read_fds, write_fds, except_fds;
};

#endif /* SERIALCOM_H_ */
