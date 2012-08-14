/*
 * DataTransceiver.cpp
 *
 *  Created on: Aug 10, 2012
 *      Author: ernad
 */

#include "DataTransceiver.h"
#include "../definitions.h"
#include "ConfigParser.h"

#include "../utility/Log.h"
#include "../comm/SerialCom.h"
#include <string.h>
#include <stdio.h>

DataTransceiver::DataTransceiver() {
	// TODO Auto-generated constructor stub

}

DataTransceiver::~DataTransceiver() {
	// TODO Auto-generated destructor stub
}

//'chEnabled' : 0,'transPos': 1,'freq1' : 3000,'dualEnabled' : 0,'freq2' : 4000
// str= "0 1 3000 0 4000"

// read config files
void DataTransceiver::init() {
	char dir[100];
	int nTemp;

	for (int i = 0; i < 4; i++) {
		sprintf(dir, "%s%s%d", TRANSCEIVER_CONFIG_DIR, "/CH", i+1);
		if (ConfigParser::readInternalParamInt(dir, "chEnabled", &nTemp)) {
			setTransceiverEnabled(i, nTemp);
		} else {
			saveTransceiverEnabled(i, DEFAULT_TRANSCEIVER_CH_ENAB);
			// saved default values
		}

		if (ConfigParser::readInternalParamInt(dir, "transPos", &nTemp)) {
			setTransceiverPos(i, nTemp);
		} else {
			saveTransceiverPos(i, DEFAULT_TRANSCEIVER_POS);
		}

		if (ConfigParser::readInternalParamInt(dir, "freq1", &nTemp)) {
			setTransceiverFreq(i, false, nTemp);
		} else {
			saveTransceiverFreq(i, false, DEFAULT_TRANSCEIVER_FREQ);
		}

		if (ConfigParser::readInternalParamInt(dir, "freq1", &nTemp)) {
			setDualEnabled(i, nTemp);
		} else {
			saveDualEnabled(i, DEFAULT_TRANSCEIVER_DUAL_ENAB);
		}

		if (ConfigParser::readInternalParamInt(dir, "freq2", &nTemp)) {
			setTransceiverFreq(i, true, nTemp);
		} else {
			saveTransceiverFreq(i, true, DEFAULT_TRANSCEIVER_FREQ);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////
bool DataTransceiver::setTransceiverEnabled(int nTransIndex, int nValue) {
	if (nValue == 0 || nValue == 1) {
		transceiver[nTransIndex].chEnabled = nValue;
		return true;
	} else {
		Log::logErrMsg("ERROR SET TRANSCEIVER ENABLED. WRONG VALUE: %d, transceiver index: %d", nValue, nTransIndex);

		return false;
	}
}

void DataTransceiver::saveTransceiverEnabled(int nTransIndex, int nValue) {
	char dir[100];

	sprintf(dir, "%s%s%d", TRANSCEIVER_CONFIG_DIR, "/CH", nTransIndex+1);

	if(setTransceiverEnabled(nTransIndex, nValue)) {
		if (ConfigParser::saveInternalParamInt(dir, "chEnabled", nValue)) {
		}
	}
}
/////////////////////////////////////////////////////////////////////////////////////////

bool DataTransceiver::setTransceiverPos(int nTransIndex, int nValue) {

	if (nValue >= 0 && nValue < 4) {// 0 = CH1, 1=CH2, 2=EXT CH1, 3=EXT CH2
		transceiver[nTransIndex].transPos = nValue;
		return true;
	} else {
		Log::logErrMsg("ERROR SET TRANSCEIVER POSITION. WRONG VALUE: %d, transceiver index: %d", nValue, nTransIndex);
		return false;
	}
}

void DataTransceiver::saveTransceiverPos(int nTransIndex, int nValue) {
	char dir[100];

	sprintf(dir, "%s%s%d", TRANSCEIVER_CONFIG_DIR, "/CH", nTransIndex+1);

	if (setTransceiverPos(nTransIndex, nValue)) {
		if (ConfigParser::saveInternalParamInt(dir, "transPos", nValue)) {
		}
	}
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
bool DataTransceiver::setDualEnabled(int nTransIndex, int nValue) {
	if (nValue == 1) {
		transceiver[nTransIndex].dualEnabled = true;
		return true;
	} else if (nValue == 0) {
		transceiver[nTransIndex].dualEnabled = false;
		return true;
	} else {
		Log::logErrMsg("ERROR SET TRANSCEIVER DUAL ENABLED. WRONG VALUE: %d, transceiver index: %d", nValue, nTransIndex);

		return false;
	}
}

void DataTransceiver::saveDualEnabled(int nTransIndex, int nValue) {
	char dir[100];

	sprintf(dir, "%s%s%d", TRANSCEIVER_CONFIG_DIR, "/CH", nTransIndex+1);

	if(setDualEnabled(nTransIndex, nValue)) {
		if (ConfigParser::saveInternalParamInt(dir, "dualEnabled", nValue)) {
		}
	}
}
/////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////

bool DataTransceiver::setTransceiverFreq(int nTransIndex, bool dual, int nValue) {
	if (nValue > 0 && nValue < 500) {// TODO: !!! Max freq?
		if(!dual)
			transceiver[nTransIndex].freq1 = nValue;
		else
			transceiver[nTransIndex].freq2 = nValue;
		return true;
	} else {
		Log::logErrMsg("ERROR SET TRANSCEIVER FREQUENCY. WRONG VALUE: %d, transceiver index: %d", nValue, nTransIndex);
		return false;
	}
}

void DataTransceiver::saveTransceiverFreq(int nTransIndex, bool dual, int nValue) {
	char dir[100];
	char temp[] ="freq1\0";

	sprintf(dir, "%s%s%d", TRANSCEIVER_CONFIG_DIR, "/CH", nTransIndex + 1);

	if (dual)
		temp[4] = '2';  //"freq2"
	if (setTransceiverFreq(nTransIndex, dual, nValue)){
		if (ConfigParser::saveInternalParamInt(dir, temp, nValue)) {
		}
	}
}
/////////////////////////////////////////////////////////////////////////////////////////

void DataTransceiver::updateObjectWithJson(Object jsonTransceiver) {
	for(int i = 0; i < 4; i++) {
		Number temp = jsonTransceiver["jsonTrans"][i]["chEnabled"];
		saveTransceiverEnabled(i, temp.Value());

		temp = jsonTransceiver["jsonTrans"][i]["transPos"];
		saveTransceiverPos(i, temp.Value());

		temp = jsonTransceiver["jsonTrans"][i]["freq1"];
		saveTransceiverFreq(i, false, temp.Value());

		temp = jsonTransceiver["jsonTrans"][i]["dualEnabled"];
		saveDualEnabled(i, temp.Value());

		temp = jsonTransceiver["jsonTrans"][i]["freq2"];
		saveTransceiverFreq(i, true, temp.Value());
	}
}

void DataTransceiver::updateOneChannelWithJson(int nIndex, Object jsonTransceiverOneChannel) {
		Number temp = jsonTransceiverOneChannel["chEnabled"];
		saveTransceiverEnabled(nIndex, temp.Value());

		temp = jsonTransceiverOneChannel["transPos"];
		saveTransceiverPos(nIndex, temp.Value());

		temp = jsonTransceiverOneChannel["freq1"];
		saveTransceiverFreq(nIndex, false, temp.Value());

		temp = jsonTransceiverOneChannel["dualEnabled"];
		saveDualEnabled(nIndex, temp.Value());

		temp = jsonTransceiverOneChannel["freq2"];
		saveTransceiverFreq(nIndex, true, temp.Value());
}

void DataTransceiver::objectToJsonMsg(char* jsonMsg) {
	sprintf(
	 jsonMsg,"{\"type\":\"transceiver\","
	 "\"jsonTrans\":[{\"type\":\"transCH1\","
			 "\"chEnabled\":%d,"
			  "\"transPos\":%d,"
			  "\"freq1\":%d,"
			  "\"dualEnabled\":%d,"
			  "\"freq2\":%d},"
		"{\"type\":\"transCH2\","
			  "\"chEnabled\":%d,"
			  "\"transPos\":%d,"
			  "\"freq1\":%d,"
			  "\"dualEnabled\":%d,"
			  "\"freq2\":%d},"
		"{\"type\":\"transCH3\","
			"\"chEnabled\":%d,"
			"\"transPos\":%d,"
			"\"freq1\":%d,"
		    "\"dualEnabled\":%d,"
			"\"freq2\":%d},"
		"{\"type\":\"transCH4\","
			"\"chEnabled\":%d,"
			"\"transPos\":%d,"
			"\"freq1\":%d,"
			"\"dualEnabled\":%d,"
			"\"freq2\":%d}]}", transceiver[0].chEnabled, transceiver[0].transPos, transceiver[0].freq1, transceiver[0].dualEnabled, transceiver[0].freq2,
			transceiver[1].chEnabled, transceiver[1].transPos, transceiver[1].freq1, transceiver[1].dualEnabled, transceiver[1].freq2,
			transceiver[2].chEnabled, transceiver[2].transPos, transceiver[2].freq1, transceiver[2].dualEnabled, transceiver[2].freq2,
			transceiver[3].chEnabled, transceiver[3].transPos, transceiver[3].freq1, transceiver[3].dualEnabled, transceiver[3].freq2);
}

void DataTransceiver::updateActiveChObjectWithJson(Object jsonActTransceiver) {
		Number temp = jsonActTransceiver["activeCh"];
		saveActiveChannel(temp.Value());

		temp = jsonActTransceiver["isActiveDual"];
		saveActiveChannelIsDual(temp.Value());
}

void DataTransceiver::objectActiveToJsonMsg(char* jsonMsg) {
	sprintf(jsonMsg, "{\"type\":\"actTrans\","
			 "\"activeCh\":%d,"
			 "\"isActiveDual\":%d}", activeCh, isActiveDual);
}

/////////////////////////////////////////////////////////////////////////////////////////
bool DataTransceiver::setActiveChannel(int nTransIndex) {
	if (nTransIndex >= 0 && nTransIndex < 4) {
		activeCh = nTransIndex;
		return true;
	} else {
		Log::logErrMsg("ERROR SET ACTIVE TRANSCEIVER. WRONG VALUE: %d", nTransIndex);

		return false;
	}
}

void DataTransceiver::saveActiveChannel(int nTransIndex) {
	if(setActiveChannel(nTransIndex)) {
		if (ConfigParser::saveInternalParamInt(TRANSCEIVER_CONFIG_DIR, "activeCh", nTransIndex)) {
		}
	}
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
bool DataTransceiver::setActiveChannelIsDual(int nValue) {
	if (nValue == 0 || nValue == 1) {
		isActiveDual = nValue;
		return true;
	} else {
		Log::logErrMsg("ERROR SET ACTIVE TRANSCEIVER IS DUAL. WRONG VALUE: %d", nValue);

		return false;
	}
}

void DataTransceiver::saveActiveChannelIsDual(int nValue) {
	if(setActiveChannelIsDual(nValue)) {
		if (ConfigParser::saveInternalParamInt(TRANSCEIVER_CONFIG_DIR, "isActiveDual", nValue)) {
		}
	}
}
/////////////////////////////////////////////////////////////////////////////////////////
