/*
 * ConfigParser.h
 *
 *  Created on: Mar 9, 2012
 *      Author: ernad
 */

#ifndef CONFIGPARSER_H_
#define CONFIGPARSER_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "DataSignal.h"

class Data;

enum EnumConfigResult{
	FOLDER_NOT_EXIST,
	FILE_NOT_EXIST,
	CONFIG_OK
};

class ConfigParser {
public:
	ConfigParser();
	virtual ~ConfigParser();
	static bool readInternalParam(const char* fileDirectory, const char* paramName, char* paramValue);
	static bool saveInternalParam(const char* fileDirectory, const char* paramName, const char* paramValue);
	static bool readInternalParamInt(const char* fileDirectory, const char* paramName, int* paramValue);
	static bool saveInternalParamInt(const char* fileDirectory, const char* paramName, int nValue);

	static EnumConfigResult existFile(const char* fileDirectory, const char* fileName);
	static bool saveOldConfig(const char* fileDirectory, const char* fileName);
	static bool readConfig(const char* fileDirectory, const char* fileName);

private:
	static void getInfoFromFile(FILE * hFile);
	static void updateParameter(char* line);
	static int getNextLine(FILE * hFile, char* line, int maxToRead);
};

#endif /* CONFIGPARSER_H_ */
