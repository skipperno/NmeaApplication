/*
 * SerialPort.cpp
 *
 *  Created on: Apr 27, 2011
 *      Author: georg
 */

#include "SerialPort.h"
#include <string.h>
#include <stdlib.h>		//not used
SerialPort::SerialPort() {
	// TODO Auto-generated constructor stub

}

SerialPort::~SerialPort() {
	// TODO Auto-generated destructor stub
}

void SerialPort::configurePort(const char nmeaport[], const char baudrate[]) {

	char ttyport[1];
	char stty[50];

	// tty port number is one less than NMEA port number
	strcpy(ttyport, nmeaport);
	ttyport[0] -= 1;

	// Build up and execute the Linux stty command
	strcpy(stty, "stty -F /dev/ttyS");
	strcat(stty, ttyport);
	strcat(stty, " ");
	strcat(stty, baudrate);
	strcat(stty, " raw -echo");
	system(stty);

}

void SerialPort::openInputPort(const char nmeaport[]) {

	char ttyport[1];
	char tty[12];

	// tty port number is one less than NMEA port number
	strcpy(ttyport, nmeaport);
	ttyport[0] -= 1;

	// Open tty port for input
	strcpy(tty, "/dev/ttyS");
	strcat(tty, ttyport);
	inpstream.open(tty, ios::out);

}

void SerialPort::openOutputPort(const char nmeaport[]) {

	char ttyport[1];
	char tty[12];

	// tty port number is one less than NMEA port number
	strcpy(ttyport, nmeaport);
	ttyport[0] -= 1;

	// Open tty port for output
	strcpy(tty, "/dev/ttyS");
	strcat(tty, ttyport);
	outstream.open(tty, ios::out);
}

void SerialPort::closeInputPort() {

	inpstream.close();
}

void SerialPort::closeOutputPort() {

	outstream.close(); // // //
}

void SerialPort::receive(char* pBuffer, int *length) {
	int nNotReceivedCounter = 0;
	char c;

	*length = 0;
	if (!inpstream.good()) {
		printf("TODO: inputstream flags in not OK.\n");
	}

	while (true) {

		if (inpstream.readsome(&c, 1) != 0) {
			nNotReceivedCounter = 0;
			pBuffer[(*length)++] = c;

		} else if(nNotReceivedCounter > 5) {
			return;
		} else {
			nNotReceivedCounter++;
			usleep(3000);
		}
	}
	//}
}

void SerialPort::send(char* pStream, int length) {

	int i;

	// Check if any valid data
	if (length == 0)
		return;

	// Send valid data to output port
	for (i = 0; i < length; i++) {
		outstream << pStream[i];
	}
	outstream.flush();

}

