/*
 * NmeaComm.cpp
 * This class will handle communication on NMEA ports
 *
 *  Created on: Apr 27, 2011
 *      Author: georg
 */

#include <string.h>
#include <stdlib.h>		//not used
#include "skipper.h"
#include "NmeaComm.h"

NmeaComm::NmeaComm() {
	// TODO Auto-generated constructor stub

}

void NmeaComm::NmeaConfigurePort(char nmeaport[], char baudrate[]) {

	char ttyport[1];
	char stty[50];

	// tty port number is one less than NMEA port number
	strcpy(ttyport, nmeaport);
	ttyport[0] -= 1;

	// Build up and execute the Linux stty command
	strcpy(stty,"stty -F /dev/ttyS");
	strcat(stty, ttyport);
	strcat(stty, " ");
	strcat(stty, baudrate);
	strcat(stty, " raw -echo");
	system(stty);

}


void NmeaComm::NmeaOpenInputPort(char nmeaport[]) {

	char ttyport[1];
	char tty[12];

	// tty port number is one less than NMEA port number
	strcpy(ttyport, nmeaport);
	ttyport[0] -= 1;

	// Open tty port for input
	strcpy(tty,"/dev/ttyS");
	strcat(tty, ttyport);
	inpstream.open(tty,ios::out);

}


void NmeaComm::NmeaOpenOutputPort(char nmeaport[]) {

	char ttyport[1];
	char tty[12];

	// tty port number is one less than NMEA port number
	strcpy(ttyport, nmeaport);
	ttyport[0] -= 1;

	// Open tty port for output
	strcpy(tty,"/dev/ttyS");
	strcat(tty, ttyport);
	outstream.open(tty,ios::out);
}

void NmeaComm::NmeaCloseInputPort() {

	inpstream.close();
}


void NmeaComm::NmeaCloseOutputPort() {

	outstream.close();
}


bool NmeaComm::NmeaInput( char* pStream, int *length) {

	char c;
	int i = 0;
	int hh_calculate = 0;
	int hh_received;


	while (inpstream.readsome(&c, 1) != 0) {
		i = 0;
		if (c == '$') {
			// NMEA sentence delimiter detected
			pStream[i++]=c;
			while (inpstream.good()) {
				// Read from wanted input Port
				c = inpstream.get();	// Get next character
				pStream[i++]=c;			// Store in array
				switch (c)
				{
					case '$' :	// Unexpected NMEA delimiter detected
						i = 0; 	// Start to check new NMEA sentence
						break;

					case '\n':	// Unexpected <LF> detected
						return false; // Illegal NMEA sentence

					case '*':	// Checksum field delimiter detected
						// Calculate checksum
						c = inpstream.get();
						pStream[i++]=c;
						if (('0' <= c) && (c <= '9')) {
							hh_received = ((int)c -'0') << 4;
						}
						else if (('A' <= c) && (c <= 'F')) {
							hh_received = ((int)c -'A' + 10) << 4;
						}
						else {
							//i = 0;
							//break;	// Illegal NMEA
							return false;	// Illegal NMEA
						}
						c = inpstream.get();
						pStream[i++]=c;
						if (('0' <= c) && (c <= '9')) {
							hh_received = hh_received + ((int)c -'0');
						}
						else if (('A' <= c) && (c <= 'F')) {
							hh_received = hh_received + ((int)c -'A' + 10);
						}
						else {
							//i = 0;
							//break;	// Illegal NMEA
							return false;	// Illegal NMEA
						}
						// Check for correct received checksum
						if (hh_received != hh_calculate) {
							i = 0; // Illegal NMEA
							//break;
							return false;	// Illegal NMEA
						}
						// Check for <CR><LF> after checksum value
						c = inpstream.get();
						pStream[i++]=c;
						if (c != '\r') { // <CR>
							//i = 0;
							//break; // Illegal NMEA
							return false;	// Illegal NMEA
						}
						c = inpstream.get();
						pStream[i++]=c;
						if (c != '\n') { // <LF>
							//i = 0;
							//break; // Illegal NMEA
							return false;	// Illegal NMEA
						}
						*length = i;
						return true; // Complete NMEA sentence received

					case '\r':	// <CR> detected
						c = inpstream.get();
						pStream[i++] = c;
						if (c == '\n') { // <LF>
							*length = i;
							return true;
						}
						else {
							//i = 0;
							//break; // Illegal NMEA
							return false;	// Illegal NMEA
						}

					default: // Accept character
						break;	// Continue reading of input stream

				} // switch

				// Legal character received, calculate checksum
				hh_calculate = hh_calculate ^ c;

			} // if (c == '$')

		} // while (inpstream.good())

	} // if (inpstream.readsome())

	*length = 0;
	return false;

}

void NmeaComm::NmeaOutput(char* pStream, int length) {

	int i;

	// Check if any valid data
	if (length == 0)
		return;

	// Send valid data to output port
	for (i=0; i<length; i++) {
		outstream << pStream[i];
	}
	outstream.flush();

}

NmeaComm::~NmeaComm() {
	// TODO Auto-generated destructor stub
}



