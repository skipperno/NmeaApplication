/*
 * NmeaMsgParser.h
 *
 *  Created on: Sep 12, 2010
 *      Author: ernad
 */

#ifndef NMEAMSGPARSER_H_
#define NMEAMSGPARSER_H_

enum NMEA_TALKER_ID {
	AP = 0, //Magnetic Autopilot
	CV, //Communications - Radio-Telephone (VHF)
	DF, //   Direction Finder
	EP, //   Emergency Position Indicating Beacon (EPIRB)
	ER, //   Engine Room Monitoring Systems
	GP, //   Global Positioning System (GPS)
	HC, //   Magnetic Compass
	HE, //   North Seeking Gyro
	IN, //   Integrated Navigation
	LC, //   Loran C
	OM, //   Omega receiver
	P, //    Proprietary Code
	RA, //   RADAR
	SD, //   Depth Sounder
	SN, //   Electronic Positioning System, other/general
	SS, //   Sounder, Scanning
	TI, //   Turn Rate Indicator
	VD, //   Velocity Sensor, Doppler, other/general
	DM, //   Velocity Sensor, Speed Log, Water, Magnetic
	VW, //   Velocity Sensor, Speed Log, Water, Mechanical
	WI, //   Weather Instruments
	YX, //   Transducer
	ZA, //   Timekeeper Atomic Clock
	ZQ, //   Timekeeper Quartz
	// 3 letter code talker ID:
	DBT, //   Depth below transducer
	GGA, //   Global positioning system fix data
	GLL, //   Geographic position, Latitude, Longitude
	HDT, //   Heading true
	MTW, //   Water temperature
	MWD, //   Wind direction
	MWV, //   Wind speed and angle
	RMC, //   Recommended minimum specific GPS/transit data
	RSD, //   RADAR system data
	VBW, //   Water referenced and ground referenced speed
	XDR, //   Transducer measurements
	ZDA, //   Time and date
	DPT, //   Depth (Ernad)
	UNKNOWN
};

enum NMEA_MSG_TYPE {
	GPGGA, GPGLL, GPZDA,
	WIMDA, WIMWD, WIMWV,
	UNKNOWN_NMEA
};

class NmeaMsgParser {
public:
	NmeaMsgParser();
	virtual ~NmeaMsgParser();

	static NMEA_TALKER_ID GetTalkerIdentifier(const char* nmeaMsgBuffer);
	static NMEA_MSG_TYPE GetGpsMsgType(const char* nmeaMsgBuffer);
	static bool ParseGPGGA(const char* nmeaMsgBuffer);

	static NMEA_MSG_TYPE GetWiMsgType(const char* nmeaMsgBuffer);
	static bool ParseWIMDA(const char* nmeaMsgBuffer);

private:
	static int getString(const char* nmeaMsgBuffer, char* destString, int nMaxLength);
};

/*


 */
//=======================================================================
/*
 $GPRMC,143327,A,5127.736,N,00235.708,W,000.0,360.0,161099,004.2,W*7B
 $GPRMC,143333,A,5127.736,N,00235.708,W,000.0,360.0,161099,004.2,W*7E
 $GPRMC,142918,V,,,,,,,161099,,*30
 $GPRMC,143333,A,5127.736,N,00235.708,W,,,161099,004.2,W*7E
 */
//=======================================================================


#endif

