/* -*-C++-*-
 *******************************************************************
 *
 * File:			$Workfile: NmeaParser.cpp $
 * RCS:          $Header: /cvsroot/stelvio/stelvio/NavStar/NmeaParser.cpp,v 1.2 2003/09/23 04:49:13 steve_l Exp $
 * Author:       Steve Loughran,
 * Created:      Jan 2000
 * Modified:		$Modtime: 00-08-23 22:53 $
 * Revision		$Revision: 1.2 $
 * Language:     C++
 * Package:      Navstar
 * Status:       Work In Progress
 * Homepage:		www.iseran.com/gps
 * @doc
 *********************************************************************/

// NmeaParser.cpp: implementation of the CNmeaParser class.
//
//////////////////////////////////////////////////////////////////////
/*
 Copyright:	Copyright (c) 2000 Steve Loughran.

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "NmeaMsgParser.h"
#include "../data/Data.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

NmeaMsgParser::NmeaMsgParser() {

}
NmeaMsgParser::~NmeaMsgParser() {

}

NMEA_TALKER_ID NmeaMsgParser::GetTalkerIdentifier(const char* nmeaMsgBuffer) {
	switch (nmeaMsgBuffer[1]) {
	/////////////////////////////////////////////////////////////
	// GP
	/////////////////////////////////////////////////////////////
	case 'G': //GPGGA, GPGLL ...
		if (nmeaMsgBuffer[2] == 'P')
			return GP;
		break;

	/////////////////////////////////////////////////////////////
	// WI (Weather Instruments)
	/////////////////////////////////////////////////////////////
	case 'W':
		if (nmeaMsgBuffer[2] == 'I')
			return WI;
		break;
	default:
		return UNKNOWN;
		break;

	}

	return UNKNOWN;
}

NMEA_MSG_TYPE NmeaMsgParser::GetGpsMsgType(const char* nmeaMsgBuffer) {
	/////////////////////////////////////////////////////////////
	// GPGGA, GPGLL, GPZDA
	/////////////////////////////////////////////////////////////

	if (memcmp(&nmeaMsgBuffer[1], "GPGGA", 5) == 0)
			return GPGGA;

	if (memcmp(&nmeaMsgBuffer[1], "GPGLL", 5) == 0)
		return GPGLL;

	if (memcmp(&nmeaMsgBuffer[1], "GPZDA", 5) == 0)
		return GPZDA;

	return UNKNOWN_NMEA;
}

NMEA_MSG_TYPE NmeaMsgParser::GetWiMsgType(const char* nmeaMsgBuffer) {
	/////////////////////////////////////////////////////////////
	// GPGGA, GPGLL, GPZDA
	/////////////////////////////////////////////////////////////

	if (memcmp(&nmeaMsgBuffer[1], "WIMDA", 5) == 0)
			return WIMDA;

	if (memcmp(&nmeaMsgBuffer[1], "WIMWD", 5) == 0)
		return WIMWD;

	if (memcmp(&nmeaMsgBuffer[1], "WIMWV", 5) == 0)
		return WIMWV;

	return UNKNOWN_NMEA;
}


bool NmeaMsgParser::ParseGPGGA(const char* nmeaMsgBuffer) {
	const char * msgBuffer = nmeaMsgBuffer;

	char n_s[2], e_w[2]; // North or South, East or West
	char sLat[64], sLon[64], hms[64];
	//char hemi, l_hemi;
	/*double mslHeight, geoidHeight, hdop;
	int nSats, fix;
	int dgpsAge, dgpsStation;
*/


	sLat[0] = 0;
	sLon[0] = 0;
	msgBuffer += 7; // move to time

	int nPos = 0;
	nPos += NmeaMsgParser::getString(&msgBuffer[nPos], hms, 15);
	nPos += NmeaMsgParser::getString(&msgBuffer[nPos], sLat, 15);
	nPos += NmeaMsgParser::getString(&msgBuffer[nPos], n_s, 2);
	nPos += NmeaMsgParser::getString(&msgBuffer[nPos], sLon, 15);
	nPos += NmeaMsgParser::getString(&msgBuffer[nPos], e_w, 2);

	Data::getInstance()->setGpsPos(n_s, sLat, e_w, sLon);
	//sscanf(msgBuffer, "%s,%s,%c,%s,%c", hms, sLat, &n_s, sLon, &e_w);

	printf("LAT: %s[%s], LON: %s[%s]\n", sLat, n_s, sLon, e_w);
	return true;
}

bool NmeaMsgParser::ParseWIMDA(const char* nmeaMsgBuffer) {
	const char * msgBuffer = nmeaMsgBuffer;

	char barPressInch[10], inch[2], barPressBars[10], bars[2];
	char airTemp[10], airTempC[2], waterTemp[10], wtCel[2];
	char relHumid[10], absHumid[10];
	char devPoint[10], devPointC[2];
	char windDirTrue[10], windT[2];
	char windDirMag[10], windM[2];
	char windSpeedKnots[10], knots[2];
	char windSpeedMet[10],  meters[2];
/*
	double mslHeight, geoidHeight, hdop;
	int nSats, fix, dgpsAge, dgpsStation;
*/
	msgBuffer += 7; // move to start

	int nPos = 0;
	nPos += NmeaMsgParser::getString(&msgBuffer[nPos], barPressInch, 10);
	nPos += NmeaMsgParser::getString(&msgBuffer[nPos], inch, 2);
	nPos += NmeaMsgParser::getString(&msgBuffer[nPos], barPressBars, 10);
	nPos += NmeaMsgParser::getString(&msgBuffer[nPos], bars, 2);

	nPos += NmeaMsgParser::getString(&msgBuffer[nPos], airTemp, 10);
	nPos += NmeaMsgParser::getString(&msgBuffer[nPos], airTempC, 2);
	nPos += NmeaMsgParser::getString(&msgBuffer[nPos], waterTemp, 10);
	nPos += NmeaMsgParser::getString(&msgBuffer[nPos], wtCel, 2);

	nPos += NmeaMsgParser::getString(&msgBuffer[nPos], relHumid, 10);
	nPos += NmeaMsgParser::getString(&msgBuffer[nPos], absHumid, 2);

	nPos += NmeaMsgParser::getString(&msgBuffer[nPos], devPoint, 10);
	nPos += NmeaMsgParser::getString(&msgBuffer[nPos], devPointC, 2);

	nPos += NmeaMsgParser::getString(&msgBuffer[nPos], windDirTrue, 10);
	nPos += NmeaMsgParser::getString(&msgBuffer[nPos], windT, 2);

	nPos += NmeaMsgParser::getString(&msgBuffer[nPos], windDirMag, 10);
	nPos += NmeaMsgParser::getString(&msgBuffer[nPos], windM, 2);

	nPos += NmeaMsgParser::getString(&msgBuffer[nPos], windSpeedKnots, 10);
	nPos += NmeaMsgParser::getString(&msgBuffer[nPos], knots, 2);

	nPos += NmeaMsgParser::getString(&msgBuffer[nPos], windSpeedMet, 10);
	nPos += NmeaMsgParser::getString(&msgBuffer[nPos], meters, 2);

	printf("WIMDA: %s[C], %s[B],  %s[m/s], %s[deg],  %s[deg]\n", airTemp, barPressBars, windSpeedMet, windDirTrue, windDirMag);

	//sscanf(msgBuffer, "%s,%s,%c,%s,%c", hms, sLat, &n_s, sLon, &e_w);
	return true;
}

int NmeaMsgParser::getString(const char* nmeaMsgBuffer, char* destString, int nMaxLength) {
	int nCounter = 0;
	destString[nCounter] = 0;

	while (nCounter < nMaxLength) {
		if(*nmeaMsgBuffer == ',') {
			destString[nCounter] = 0;
			nCounter++; // include ','
			return nCounter;
		} else {
			destString[nCounter++] = *(nmeaMsgBuffer++);
		}
	}

	destString[nCounter] = 0;

	return nCounter;
}

//=======================================================================
/**
 @func	parse a sentence
 @parm	zero terminated string
 @rdesc	true if the data has changed something
 */
//=======================================================================
/*
bool NmeaMsgParser::Parse(const char* nmeaMsgBuffer) {
	bool bParsed = false;
	CToyString nmeaCode;
	CToyString nmeaData;
	//base sanity check
	if (strlen(nmeaMsgBuffer) < 7 || nmeaMsgBuffer[0] != '$'
			|| nmeaMsgBuffer[6] != ',' || !VerifyChecksum(sentence)) {
		return false;
	}

	GetOwnerNavInfo();
	nmeaCode.AssignSubstring(sentence + 1, 5);
	int l = (int) _tcslen(sentence + 6);
	nmeaData.AssignSubstring(sentence + 6, l - 3);
	//look at what string is received and parse them
	//appropriately.
	//add new strings at the end
	//SPEED: look at the logs, see which ones are most frequent
	//and test first
	if (nmeaCode.Equals(_T("GPGLL"))) {
		bParsed = ParseGLL(nmeaData.c_str());
	} else if (nmeaCode.Equals(_T("GPRMC"))) {
		bParsed = ParseRMC(nmeaData.c_str());
	} else if (nmeaCode.Equals(_T("GPGSA"))) {
		bParsed = ParseGSA(nmeaData.c_str());
	} else if (nmeaCode.Equals(_T("GPGGA"))) {
		bParsed = ParseGGA(nmeaData.c_str());
	} else if (nmeaCode.Equals(_T("GPGSV"))) {
		bParsed = ParseGSV(nmeaData.c_str());
	}

	if (bParsed) //&& m_navInfo.m_changed!=change_nothing)
		SetOwnerNavInfo();
	return bParsed;
}

*/


//=======================================================================
/**
 @mfunc	parse a GPGGA sentence. another complex bugger
 @parm	zero terminated data string
 @rdesc	true if the data has changed something

 $GPGGA,142917,,,,,0,00,,,M,,M,,*6E
 $GPGGA,142957,5127.736,N,00235.708,W,1,08,2.0,-128.5,M,50.0,M,,*78
 $GPGGA,143348,5127.736,N,00235.708,W,1,09,2.0,-128.5,M,50.0,M,,*7C

 */
; /*
 ** GGA - Global Positioning System Fix Data
 ** Time, Position and fix related data fora GPS receiver.
 **
 **                                                      11
 **        1         2       3 4        5 6 7  8   9  10 |  12 13  14   15
 **        |         |       | |        | | |  |   |   | |   | |   |    |
 ** $--GGA,hhmmss.ss,llll.ll,a,yyyyy.yy,a,x,xx,x.x,x.x,M,x.x,M,x.x,xxxx*hh<CR><LF>
 **
 ** Field Number:
 **  1) Universal Time Coordinated (UTC)
 **  2) Latitude
 **  3) N or S (North or South)
 **  4) Longitude
 **  5) E or W (East or West)
 **  6) GPS Quality Indicator,
 **     0 - fix not available,
 **     1 - GPS fix,
 **     2 - Differential GPS fix
 **  7) Number of satellites in view, 00 - 12
 **  8) Horizontal Dilution of precision
 **  9) Antenna Altitude above/below mean-sea-level (geoid)
 ** 10) Units of antenna altitude, meters
 ** 11) Geoidal separation, the difference between the WGS-84 earth
 **     ellipsoid and mean-sea-level (geoid), "-" means mean-sea-level
 **     below ellipsoid
 ** 12) Units of geoidal separation, meters
 ** 13) Age of differential GPS data, time in seconds since last SC104
 **     type 1 or 9 update, null field when DGPS is not used
 ** 14) Differential reference station ID, 0000-1023
 ** 15) Checksum
 */

//=======================================================================
/*
bool NmeaMsgParser::ParseGGA(const char* nmeaMsgBuffer) {
	const char * msgBuffer = nmeaMsgBuffer;

	char n_s, e_w; // North or South, East or West
	char sLat[64], sLon[64], hemi, l_hemi, hms[64];
	double mslHeight, geoidHeight, hdop;
	int nSats, fix, dgpsAge, dgpsStation;

	msgBuffer += 6; // move to time

	sscanf(msgBuffer, "%s,%s,%c,%s,%c", hms, sLat, n_s, sLon, e_w);
	return true;
}

	GetStringFromString(sentence, hms, sizeof(hms) - 1);
	SkipComma(sentence);
	GetStringFromString(sentence, sLat, sizeof(sLat) - 1);
	SkipComma(sentence);
	GetCharFromString(sentence, &hemi);
	SkipComma(sentence);
	GetStringFromString(sentence, sLong, sizeof(sLong) - 1);
	SkipComma(sentence);
	GetCharFromString(sentence, &l_hemi);
	SkipComma(sentence);
	fix = GetIntFromString(sentence, 0);
	SkipComma(sentence);
	nSats = GetIntFromString(sentence, 0);
	SkipComma(sentence);
	GetDoubleFromString(sentence, &hdop, 0);
	SkipComma(sentence);
	GetDoubleFromString(sentence, &mslHeight, 0);
	SkipComma(sentence);
	SkipExpectedChar(sentence, _T('M'));
	SkipComma(sentence);
	GetDoubleFromString(sentence, &geoidHeight, 0);
	SkipComma(sentence);
	SkipExpectedChar(sentence, _T('M'));
	SkipComma(sentence);
	if (fix == 2) {
		dgpsAge = GetIntFromString(sentence, 0);
		SkipComma(sentence);
		dgpsStation = GetIntFromString(sentence, 0);
	}
	bool bChanged = false;
	fix_quality q = fix_no_fix;
	if (fix == 0)
		q = fix_no_fix;
	else if (fix == 1)
		q = m_navInfo.m_quality; //REVISIT whatever we have already
	else if (fix == 2)
		q = fix_dgps;

	//dont report a change when fix q. is unchanged
	if (m_navInfo.m_quality != q) {
		m_navInfo.m_quality = q;
		bChanged = true;
	}

	//only act on valid data.
	if (fix != 0) {
		SetLatLong(sLat, hemi, sLong, l_hemi);
		SetAltitude(mslHeight);
		bChanged = true;
	}

	return bChanged;*/

//=======================================================================
/**
 @mfunc	parse a sentence
 @parm	zero terminated data string
 @rdesc	true if the data has changed something
 
 $GPGLL,,,,,142918,*57 ;!parsed but not handled!
 $GPGLL,5127.736,N,00235.708,W,143349,	;ok
 $GPGLL,5127.736,S,00235.708,E,143344,	;ok

 */
//=======================================================================
/*
bool NmeaMsgParser::ParseGLL(LPCTSTR sentence) {
	TCHAR sLat[64], sLong[64], hemi, l_hemi, hms[64];
	int c;
	c = _stscanf(sentence, _T(",%[0-9.],%c,%[0-9.],%c,%[0-9],"), sLat, &hemi,
			sLong, &l_hemi, hms);

	if (c == 5) {
		return SetLatLong(sLat, hemi, sLong, l_hemi);
	} else
		return false;
}
*/
//=======================================================================
/**
 @mfunc	parse a GPRMC sentence. One complex bugger
 @parm	zero terminated data string
 @rdesc	true if the data has changed something
 
 $GPRMC,143327,A,5127.736,N,00235.708,W,000.0,360.0,161099,004.2,W*7B
 $GPRMC,143333,A,5127.736,N,00235.708,W,000.0,360.0,161099,004.2,W*7E
 $GPRMC,142918,V,,,,,,,161099,,*30
 $GPRMC,143333,A,5127.736,N,00235.708,W,,,161099,004.2,W*7E

 */
/*
 ** RMC - Recommended Minimum Navigation Information
 **                                                            12
 **        1         2 3       4 5        6 7   8   9    10  11|
 **        |         | |       | |        | |   |   |    |   | |
 ** $--RMC,hhmmss.ss,A,llll.ll,a,yyyyy.yy,a,x.x,x.x,xxxx,x.x,a*hh<CR><LF>
 **
 ** Field Number:
 **  1) UTC Time
 **  2) Status, V = Navigation receiver warning
 **  3) Latitude
 **  4) N or S
 **  5) Longitude
 **  6) E or W
 **  7) Speed over ground, knots
 **  8) Track made good, degrees true
 **  9) Date, ddmmyy
 ** 10) Magnetic Variation, degrees
 ** 11) E or W
 ** 12) Checksum
 */

//=======================================================================
/*
bool NmeaMsgParser::ParseRMC(LPCTSTR sentenceIn) {
	TCHAR sLat[64], sLong[64], hemi, l_hemi, hms[64];
	TCHAR dmy[16];
	double speed, bearing, mag_bearing;
	TCHAR mag_hemi, status;
	bool bVector;
	LPCSTR *sentence = &sentenceIn;
	SkipComma(sentence);
	GetStringFromString(sentence, hms, sizeof(hms) - 1);
	SkipComma(sentence);
	GetCharFromString(sentence, &status);
	SkipComma(sentence);
	GetStringFromString(sentence, sLat, sizeof(sLat) - 1);
	SkipComma(sentence);
	GetCharFromString(sentence, &hemi);
	SkipComma(sentence);
	GetStringFromString(sentence, sLong, sizeof(sLong) - 1);
	SkipComma(sentence);
	GetCharFromString(sentence, &l_hemi);
	SkipComma(sentence);
	bVector = GetDoubleFromString(sentence, &speed, 0);
	SkipComma(sentence);
	GetDoubleFromString(sentence, &bearing, 0);
	SkipComma(sentence);
	GetStringFromString(sentence, dmy, sizeof(dmy) - 1);
	SkipComma(sentence);
	GetDoubleFromString(sentence, &mag_bearing, 0);
	SkipComma(sentence);
	GetCharFromString(sentence, &mag_hemi);

	//only act on valid data. that includes the clock, which can
	//often be grabbed
	if (status == _T('A')) {
		SetLatLong(sLat, hemi, sLong, l_hemi);
		if (bVector)
			SetVector(bearing, speed, unit_knot);
		SetTime(hms, dmy);
		return true;
	} else
		return false;
}*/

//=======================================================================
/**
 @mfunc	parse a GPGSA sentence. Satellite availability.
 we only care about fix quality, as real sat info comes elsewhere
 @parm	zero terminated data string
 @rdesc	true if the data was parsed

 $GPGSA,A,1,,,,,,,,,,,,,,,
 $GPGSA,A,3,02,,,09,10,13,17,23,26,27,,,4.5,2.0,3.0
 $GPGSA,A,2,02,,,09,10,13,17,23,26,27,,,4.5,2.0,3.0
 $GPGSA,A,2,09,08,05,26,07,23,21,29,09,08,05,26,,100,*22


 */
//=======================================================================
/*
bool NmeaMsgParser::ParseGSA(LPCTSTR sentenceIn) {
	bool bUpdated = false;
	int fix;
	TCHAR status;
	LPCSTR *sentence = &sentenceIn;
	SkipComma(sentence);
	GetCharFromString(sentence, &status);
	SkipComma(sentence);
	fix = GetIntFromString(sentence, 1);
	int satcount = 0;

	//only act on valid data. that includes the clock, which can
	//often be grabbed
	fix_quality q = fix_no_fix;

	if (status == _T('A')) {
		if (fix == 1)
			q = fix_no_fix;
		else if (fix == 2)
			q = fix_gps_2D;
		else if (fix == 3)
			q = fix_gps_3D;
	}

	//get satellite data
	int prn;
	for (int i = 0; i < 12; i++) {
		SkipComma(sentence);
		prn = GetIntFromString(sentence, 0);
		if (prn > 0) {
			satcount++;
			if (satcount == 1) {
				//				m_navInfo.m_constellation.Clear();
			}
			AddSatellite(prn, 0, 0, 0, 1, 0,
					satellite_no_bearing | satellite_no_signal);
		}
	}
	double pdop, hdop, vdop;
	GetDoubleFromString(sentence, &pdop, 100);
	SkipComma(sentence);
	GetDoubleFromString(sentence, &hdop, 100);
	SkipComma(sentence);
	GetDoubleFromString(sentence, &vdop, 100);
	SkipComma(sentence);

	if (satcount > 0) {
		m_navInfo.m_constellation.m_nTrackedSatellites = satcount;
		m_navInfo.touch(change_height);
		m_navInfo.touch(change_constellation);
		bUpdated = true;
	}

	if (hdop != m_navInfo.hdop) {
		m_navInfo.hdop = q;
		m_navInfo.touch(change_dop);
		bUpdated = true;
	}

	if (m_navInfo.m_quality != q) {
		m_navInfo.m_quality = q;
		bUpdated = true;
	}
	return bUpdated;
}
*/

//=======================================================================
/**
 @func verify a checksum string
 @parm	in string "$something*HH"
 @rdesc	true if the xor of all between $ and * match the two hex values
 */
//=======================================================================
/*
bool NmeaMsgParser::VerifyChecksum(LPCTSTR sentence) {
	BYTE b = 0;
	TCHAR c;
	if (*sentence++ != _T('$'))
		return false;
	while ((c = *sentence++) && (c != _T('*'))) {
		b ^= BYTE(c);
	}
	//no checksum
	if (c != _T('*'))
		return false;
	else {
		TCHAR n1, n2;
		int checksum;
		n1 = *(sentence);
		if (n1)
			n2 = *(sentence + 1);
		else
			n2 = 0;
		checksum = ConvertFromHexCharToInt(n1, 0xffff) * 16
				+ ConvertFromHexCharToInt(n2, 0xffff);
		return checksum == b;
	}
}
*/
//=======================================================================
/**
 @mfunc	parse a GPGSV sentence, covering satellite bearing & strength
 @parm	zero terminated data string
 @rdesc	true if the data was parsed

 $GPGSV,3,1,11,02,52,086,48,07,03,119,00,08,04,244,00,09,27,245,43*77
 $GPGSV,3,2,11,10,28,181,43,13,24,114,42,17,17,283,40,23,23,316,42*75
 $GPGSV,3,3,11,26,79,292,51,27,25,068,43,31,04,015,00,,,,*47

 $GPGSV,3,1,11,02,52,087,00,07,03,119,00,08,04,244,00,09,27,245,00*7D
 $GPGSV,3,2,11,10,28,181,00,13,24,114,00,17,18,283,00,23,22,316,00*78
 $GPGSV,3,3,11,26,79,292,00,27,25,068,00,31,04,016,00,,,,*47

 */
//=======================================================================
/*
bool NmeaMsgParser::ParseGSV(LPCTSTR sentenceIn) {
	bool bUpdated = false;
	LPCSTR *sentence = &sentenceIn;
	SkipComma(sentence);
	int nSentences = GetIntFromString(sentence, 0);
	SkipComma(sentence);
	int nCurrentSentence = GetIntFromString(sentence, 0);
	if (!nSentences || !nCurrentSentence)
		return false;

	//first sentence is special
	if (nCurrentSentence == 1) {
		for (int i = 0; i < satellite_count; i++) {
			m_navInfo.m_constellation.m_satellites[i].m_tag = -1;
			m_navInfo.m_constellation.m_nTrackedSatellites = 0;
		}
	}
	SkipComma(sentence);
	int nSatellites = GetIntFromString(sentence, 0);
	SkipComma(sentence);

	int satcount = 0;

	//get 0-4 satellite data sets
	int prn;
	int bearing, elevation, signal;
	for (int i = 0; i < 4; i++) {
		prn = GetIntFromString(sentence, -1);
		if (prn == -1)
			break;
		SkipComma(sentence);
		elevation = GetIntFromString(sentence, 0);
		SkipComma(sentence);
		bearing = GetIntFromString(sentence, 0);
		SkipComma(sentence);
		signal = GetIntFromString(sentence, 0);
		SkipComma(sentence);
		satcount++;
		AddSatellite(prn, bearing, elevation, signal, 0, 0, 0);
	}

	m_navInfo.m_constellation.m_nTrackedSatellites += satcount;
	m_navInfo.m_constellation.BuildFlagsFromSignal();

	//sentence set complete: act time
	if (nSentences == nCurrentSentence) {
		//scrub invalids
		for (int i = 0; i < satellite_count; i++) {
			if (m_navInfo.m_constellation.m_satellites[i].m_tag == -1) {
				m_navInfo.m_constellation.m_satellites[i].m_bValid = false;
			}
		}
		//act on valids
		m_navInfo.touch(change_constellation);
		bUpdated = true;
	}

	return true;
}
*/
