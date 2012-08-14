/*
 * InitMultiBox.cpp
 *
 *  Created on: Mar 9, 2012
 *      Author: ernad
 */

#include "InitMultiBox.h"
#include "utility/Log.h"
#include "utility/SysTime.h"
#include "definitions.h"

#include "data/ConfigParser.h"
#include "data/Data.h"

#include <sys/stat.h>
#include <errno.h>
#include <pthread.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

InitMultiBox::InitMultiBox() {
	// TODO Auto-generated constructor stub

}

InitMultiBox::~InitMultiBox() {
	// TODO Auto-generated destructor stub
}

bool InitMultiBox::searchNewConfiguration() {
	char tmpString[100];
	char date[12];
	char time[12];

	Data::getInstance(); // just for initializing

	ConfigParser::saveOldConfig("/opt", "myTestConfig.txt");

	EnumConfigResult confRes = ConfigParser::existFile(SD_CARD_DIR, NEW_CONFIG_FILE);
	if (confRes != CONFIG_OK ) {
		Log::logDbgMsg("OK. Not found new configuration on SD card");
		return false;
	}
	SysTime::sysTime_toString3(date, time);
	// save a copy of the new config to the SD card
	sprintf(tmpString, "%s%s_%s.txt", "oldConfig_used_before_", date, time);
	//system(tmpString);
	ConfigParser::saveOldConfig(SD_CARD_DIR, tmpString);

	ConfigParser::readConfig(SD_CARD_DIR, NEW_CONFIG_FILE);

	return true;
}

/**
 * Use this e.g. when missing config file (create default config)
 */
bool InitMultiBox::setDefaultConfiguration() {
	// done by DataSignal ... ??? don't needs
	//ConfigMain configMain;
	//return ConfigParser::saveNewConfig(MAIN_CONFIG_DIR, MAIN_CONFIG_FILE, &configMain);
	return true;
}

bool InitMultiBox::setConfiguration() {
	// don't needs, done by dataSignal.init() ... ?????
	/*ConfigMain* pConfigMain;
	pConfigMain = ConfigParser::readConfig(MAIN_CONFIG_DIR, MAIN_CONFIG_FILE);

	Data::setGain(pConfigMain->gain);*/
	return true;
}

