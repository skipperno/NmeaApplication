/*
 * NmeaComm.h
 * This class will handle communication on NMEA ports
 *
 *  Created on: Apr 27, 2011
 *      Author: georg
 */

#ifndef NMEACOMM_H_
#define NMEACOMM_H_

#include <iostream>
#include <fstream>

using namespace std;

class NmeaComm
{

	ifstream inpstream;
	ofstream outstream;

public:

	NmeaComm();										// Constructor
	void NmeaConfigurePort(char nmeaport[], char baudrate[]);
													// Configure nmea port
	void NmeaOpenInputPort(char nmeaport[]);		// Open nmea input port
	void NmeaOpenOutputPort(char nmeaport[]);		// Open nmea output port
	void NmeaCloseInputPort();						// Close nmea inport port
	void NmeaCloseOutputPort();						// Close nmea output port
	bool NmeaInput(char* pStream, int *length);		// Read from nmea input port
	void NmeaOutput(char* pStream, int length);		// Send to nmea output port
	~NmeaComm();									// Deconstructor

//	char Stream[1024];	// Storage of current stream
};

#endif /* NMEACOMM_H_ */
