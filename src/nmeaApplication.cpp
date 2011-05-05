//============================================================================
// Name        : NmeaApplication.cpp
// Author      : Georg Boasson
// Version     :
// Copyright   : SKIPPER Electronics AS
// Description : Demo Application for reading two NMEA ports
//				 and sending both data streams out on one NMEA port
//============================================================================

#include <iostream>
#include "skipper.h"
#include "NmeaComm.h"

using namespace std;


void nmeaApplication()
{
	NmeaComm stream1;
	NmeaComm stream2;

	char stream[1024];			// Storage of NMEA data stream
	char* pStream = stream;		// Pointer to storage of NMEA data stream
	int  length,i;				// Length of NMEA data stream

	char baud4800[] = "4800";	// Input/output baudrate to be fetched from configuration-file or web-configuration
	char nmea2[] = "2";			// Input NMEA port number to be fetched from configuration-file or web-configuration
	char nmea3[] = "3";			// Input NMEA port number to be fetched from configuration-file or web-configuration

	stream1.NmeaConfigurePort(nmea2, baud4800);
	stream1.NmeaOpenInputPort(nmea2);
	stream1.NmeaOpenOutputPort(nmea2);
	stream2.NmeaConfigurePort(nmea3, baud4800);
	stream2.NmeaOpenInputPort(nmea3);
	stream2.NmeaOpenOutputPort(nmea2);

	for (;;) {

		if(stream1.NmeaInput(pStream, &length)) {
			stream1.NmeaOutput(pStream, length);
			for (i=0; i<length; i++) {
				if (pStream[i] == '\n')
					cout << "<LF>";
				else if (pStream[i] == '\r')
					cout << "<CR>";
				else
					cout << pStream[i];
			}
			cout << endl;
		}

		if(stream2.NmeaInput(pStream, &length)) {
			stream2.NmeaOutput(pStream, length);
			for (i=0; i<length; i++) {
				if (pStream[i] == '\n')
					cout << "<LF>";
				else if (pStream[i] == '\r')
					cout << "<CR>";
				else
					cout << pStream[i];
			}
			cout << endl;
		}

	}

	stream1.NmeaCloseInputPort();
	stream1.NmeaCloseOutputPort();
	stream2.NmeaCloseInputPort();
	stream2.NmeaCloseOutputPort();

}



int main() {
	cout << "Hei 1 !!!" << endl; // prints !!!Hello World!!!
	nmeaApplication();
	return 0;
}
