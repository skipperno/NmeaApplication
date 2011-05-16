/*
 * SerialPort.h
 *
 *  Created on: May 12, 2011
 *      Author: eno
 */

#ifndef SERIALPORT_H_
#define SERIALPORT_H_

#include <iostream>
#include <fstream>

using namespace std; // needs for "ifstream" and "ofstream"

class SerialPort {


public:
	SerialPort();
	virtual ~SerialPort();

	void configurePort(const char nmeaport[], const char baudrate[]);
	void openInputPort(const char nmeaport[]);
	void openOutputPort(const char nmeaport[]);
	void closeInputPort();
	void closeOutputPort();
	void receive( char* pStream, int *length);
	void send(char* pStream, int length);

private:
	ifstream inpstream;
	ofstream outstream;
};

#endif /* SERIALPORT_H_ */
