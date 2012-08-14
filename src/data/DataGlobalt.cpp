/*
 * DataGlobalt.cpp
 *
 *  Created on: Mar 15, 2012
 *      Author: ernad
 */

#include "DataGlobalt.h"
#include "../definitions.h"
#include "ConfigParser.h"

#include "../utility/Log.h"
#include "../comm/SerialCom.h"
#include <string.h>
#include <stdio.h>

DataGlobalt::DataGlobalt() {
	strcpy(ip, "0.0.0.0"); // will be changed in the init
}

DataGlobalt::~DataGlobalt() {
	// TODO Auto-generated destructor stub
}

// read config files
void DataGlobalt::init() {
	char temp[100];

	if (ConfigParser::readInternalParam(MAIN_CONFIG_DIR, "ip", temp)) {
		setIp(temp);
	} else {
		saveIp( DEFAULT_MULTIBOX_IP); // saved default values
	}

	if (ConfigParser::readInternalParam(MAIN_CONFIG_DIR, "baudCom1", temp)) {
		setBaudCom1(temp);
		} else {
			saveBaudCom1( SerialCom::getBaudByIndex(DEFAULT_BAUD_RATE_INDEX)); // saved default values
		}

	if (ConfigParser::readInternalParam(MAIN_CONFIG_DIR, "baudCom2", temp)) {
		setBaudCom2(temp);
		} else {
			saveBaudCom2( SerialCom::getBaudByIndex(DEFAULT_BAUD_RATE_INDEX)); // saved default values
		}

	if (ConfigParser::readInternalParam(MAIN_CONFIG_DIR, "baudCom3", temp)) {
		setBaudCom3(temp);
		} else {
			saveBaudCom3( SerialCom::getBaudByIndex(DEFAULT_BAUD_RATE_INDEX)); // saved default values
		}
}


void DataGlobalt::saveIp(const char* newValue) {
	// TODO: validate
	//if (newValue < 0 || newValue > 100) {
		//Log::logErrMsg("ERROR SAVING GAIN. WRONG VALUE: %s", newValue);
	//} else {
		if (strcmp(ip, newValue) != 0) {
			strcpy(ip, newValue);
			if (ConfigParser::saveInternalParam(MAIN_CONFIG_DIR, "ip", ip)) {
			}
		}
	//}
}

void DataGlobalt::saveBaudCom1(int newValue) {
	char temp[10];
	baudCom1 = newValue; //SerialCom::getBaudByIndex(newValue);
	sprintf(temp, "%d", baudCom1);
	ConfigParser::saveInternalParam(MAIN_CONFIG_DIR, "baudCom1", temp);
}
void DataGlobalt::saveBaudCom2(int newValue) {
	char temp[10];
	baudCom2 = newValue; //SerialCom::getBaudByIndex(newValue);
	sprintf(temp, "%d", baudCom2);
	ConfigParser::saveInternalParam(MAIN_CONFIG_DIR, "baudCom2", temp);
}
void DataGlobalt::saveBaudCom3(int newValue) {
	char temp[10];
	baudCom3 = newValue; //SerialCom::getBaudByIndex(newValue);
	sprintf(temp, "%d", baudCom3);
	ConfigParser::saveInternalParam(MAIN_CONFIG_DIR, "baudCom3", temp);
}


void DataGlobalt::updateObjectWithJson(Object json) {
	String temp = json["ip"];
	saveIp((const char*)temp.Value().c_str());
}

void DataGlobalt::objectToJsonMsg(char* jsonMsg) {
	sprintf(jsonMsg, "{\"type\":\"glob\",\"ip\":%s}", ip);
}

// private. Used in init when reading config file
void DataGlobalt::setIp(const char* newValue) {
	// TODO: validate
	strcpy(ip, newValue);
}

void DataGlobalt::setBaudCom1(const char* newValue) {
	// TODO: validate
	baudCom1 = atoi(newValue);
}

void DataGlobalt::setBaudCom2(const char* newValue) {
	// TODO: validate
	baudCom2 = atoi(newValue);
}

void DataGlobalt::setBaudCom3(const char* newValue) {
	// TODO: validate
	baudCom3 = atoi(newValue);
}
