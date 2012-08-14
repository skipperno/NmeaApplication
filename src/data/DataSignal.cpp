/*
 * ObjectSignal.cpp
 *
 *  Created on: Mar 13, 2012
 *      Author: ernad
 */

#include "DataSignal.h"
#include "../definitions.h"
#include "ConfigParser.h"

#include "../utility/Log.h"
#include <string.h>
#include <stdio.h>

DataSignal::DataSignal() {
	gain = -1;
	tvg = -1;
	freq = -1;
	pow = -1;
	alarmL = -1;
	alarmH = -1;
	range = -1;
}

DataSignal::~DataSignal() {
	// TODO Auto-generated destructor stub
}

// read config files
void DataSignal::init() {
	char temp[100];

	if (ConfigParser::readInternalParam(MAIN_CONFIG_DIR, "gain", temp)) {
		setGain(temp);
	} else {
		saveGain( DEFAULT_GAIN); // saved default values
	}

	if (ConfigParser::readInternalParam(MAIN_CONFIG_DIR, "tvg", temp)) {
		setTvg(temp);
	} else {
		saveTvg( DEFAULT_TVG); // saved default values
	}

	if (ConfigParser::readInternalParam(MAIN_CONFIG_DIR, "freq", temp)) {
		setFreq(temp);
	} else {
		saveFreq( DEFAULT_FREQ); // saved default values
	}

	if (ConfigParser::readInternalParam(MAIN_CONFIG_DIR, "pow", temp)) {
		setPower(temp);
	} else {
		savePow( DEFAULT_POW); // saved default values
	}

	if (ConfigParser::readInternalParam(MAIN_CONFIG_DIR, "alarmL", temp)) {
		setAlarmL(temp);
	} else {
		saveAlarmL( DEFAULT_ALARML); // saved default values
	}

	if (ConfigParser::readInternalParam(MAIN_CONFIG_DIR, "alarmH", temp)) {
		setAlarmH(temp);
	} else {
		saveAlarmH( DEFAULT_ALARMH); // saved default values
	}

	if (ConfigParser::readInternalParam(MAIN_CONFIG_DIR, "range", temp)) {
		setRange(temp);
	} else {
		saveRange( DEFAULT_RANGE); // saved default values
	}
}


void DataSignal::saveGain(int newValue) {
	char temp[100];
	if (newValue < 0 || newValue > 100) {
		Log::logErrMsg("ERROR SAVING GAIN. WRONG VALUE: %s", newValue);
	} else {
		if (gain != newValue) {
			gain = newValue;
			sprintf(temp, "%d", gain);
			if (ConfigParser::saveInternalParam(MAIN_CONFIG_DIR, "gain", temp)) {
			}
		}
	}
}

void DataSignal::saveTvg(int newValue) {
	char temp[100];
	if (newValue < 0 || newValue > 100) {
		Log::logErrMsg("ERROR SAVING TVG. WRONG VALUE: %s", newValue);
	} else {
		if (tvg != newValue) {
			tvg = newValue;
			sprintf(temp, "%d", tvg);
			if (ConfigParser::saveInternalParam(MAIN_CONFIG_DIR, "tvg", temp)) {
			}
		}
	}
}

void DataSignal::saveFreq(int newValue) {
	char temp[100];
	// TODO: max and min freq?
	//	if (newValue < 0 || newValue > 100) {
	//			Log::logErrMsg("ERROR SAVING FREQUNECY. WRONG VALUE: %s", newValue);
	//	} else {
	if (freq != newValue) {
		freq = newValue;
		sprintf(temp, "%d", freq);
		if (ConfigParser::saveInternalParam(MAIN_CONFIG_DIR, "freq", temp)) {
		}
	}
	//	}
}

void DataSignal::savePow(int newValue) {
	char temp[100];
	if (newValue < 0 || newValue > 100) {
		Log::logErrMsg("ERROR SAVING POWER. WRONG VALUE: %s", newValue);
	} else {
		if (pow != newValue) {
			pow = newValue;
			sprintf(temp, "%d", pow);
			if (ConfigParser::saveInternalParam(MAIN_CONFIG_DIR, "pow", temp)) {
			}
		}
	}
}

void DataSignal::saveAlarmL(int newValue) {
	char temp[100];
	if (newValue < 0 || newValue > 1600) { //TODO:
		Log::logErrMsg("ERROR SAVING ALARM_L. WRONG VALUE: %s", newValue);
	} else {
		if (alarmL != newValue) {
			alarmL = newValue;
			sprintf(temp, "%d", alarmL);
			if (ConfigParser::saveInternalParam(MAIN_CONFIG_DIR, "alarmL", temp)) {
			}
		}
	}
}

void DataSignal::saveAlarmH(int newValue) {
	char temp[100];
	if (newValue < 0 || newValue > 1600) {
		Log::logErrMsg("ERROR SAVING ALARM_H. WRONG VALUE: %s", newValue);
	} else {
		if (alarmH != newValue) {
			alarmH = newValue;
			sprintf(temp, "%d", alarmH);
			if (ConfigParser::saveInternalParam(MAIN_CONFIG_DIR, "alarmH", temp)) {
			}
		}
	}
}

void DataSignal::saveRange(int newValue) {
	char temp[100];
	if (newValue < 0 || newValue > 5) {
		Log::logErrMsg("ERROR SAVING RANGE. WRONG VALUE: %s", newValue);
	} else {
		if (range != newValue) {
			range = newValue;
			sprintf(temp, "%d", range);
			if (ConfigParser::saveInternalParam(MAIN_CONFIG_DIR, "range", temp)) {
			}
		}
	}
}

void DataSignal::updateObjectWithJson(Object jsonSignal) {
	Number temp = jsonSignal["signal"]["GAIN"];
	saveGain(temp.Value());

	temp = jsonSignal["signal"]["TVG"];
	saveTvg(temp.Value());

	temp = jsonSignal["signal"]["FREQ"];
	saveFreq(temp.Value());

	temp = jsonSignal["signal"]["POW"];
	savePow(temp.Value());

	temp = jsonSignal["alarm"]["L"];
	saveAlarmL(temp.Value());

	temp = jsonSignal["alarm"]["H"];
	saveAlarmH(temp.Value());

	temp = jsonSignal["range"];
	saveRange(temp.Value());
}

void DataSignal::objectToJsonMsg(char* jsonMsg) {
	sprintf(
			jsonMsg,
			"{\"type\":\"sig\",\"signal\":{\"GAIN\":%d,\"TVG\":%d,\"FREQ\":%d,\"POW\":%d},\"alarm\":{\"L\":%d,\"H\":%d},\"range\":%d}",
			gain, tvg, freq, pow, alarmL, alarmH, range);
}

void DataSignal::setGain(const char* gainStr) {
	int tempGain = atoi(gainStr);
	if (tempGain < 0 || tempGain > 100) {
		Log::logErrMsg("ERROR READING CONFIG. WRONG GAIN VALUE: %s", gainStr);
	} else {
		gain = tempGain;
	}
}

void DataSignal::setTvg(const char* tvgStr) {
	int temp = atoi(tvgStr);
	if (temp < 0 || temp > 100) {
		Log::logErrMsg("ERROR READING CONFIG. WRONG TVG VALUE: %s", tvgStr);
	} else {
		tvg = temp;
	}
}

void DataSignal::setFreq(const char* freqStr) {
	int temp = atoi(freqStr);
	if (temp < 0 || temp > 100) {
		Log::logErrMsg("ERROR READING CONFIG. WRONG FREQ VALUE: %s", freqStr);
	} else {
		freq = temp;
	}
}

void DataSignal::setPower(const char* powStr) {
	int temp = atoi(powStr);
	if (temp < 0 || temp > 100) {
		Log::logErrMsg("ERROR READING CONFIG. WRONG POWER VALUE: %s", powStr);
	} else {
		pow = temp;
	}
}

void DataSignal::setAlarmL(const char* alStr) {
	int temp = atoi(alStr);
	if (temp < 0 || temp > 1600) {
		Log::logErrMsg("ERROR READING CONFIG. WRONG ALARM_L VALUE: %s", alStr);
	} else {
		alarmL = temp;
	}
}

void DataSignal::setAlarmH(const char* alStr) {
	int temp = atoi(alStr);
	if (temp < 0 || temp > 1600) {
		Log::logErrMsg("ERROR READING CONFIG. WRONG ALARM_H VALUE: %s", alStr);
	} else {
		alarmH = temp;
	}
}

void DataSignal::setRange(const char* rangeStr) {
	int temp = atoi(rangeStr);
	if (temp < 0 || temp > 5) {
		Log::logErrMsg("ERROR READING CONFIG. WRONG RANGE VALUE: %s", rangeStr);
	} else {
		range= temp;
	}
}
