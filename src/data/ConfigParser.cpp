/*
 * ConfigParser.cpp
 *
 *  Created on: Mar 9, 2012
 *      Author: ernad
 */

#include "ConfigParser.h"
#include "../definitions.h"
#include "Data.h"
//#include "VtFileInfo.h"


#include <sys/stat.h>
#include <errno.h>
#include <pthread.h>

#include "../utility/Log.h"

static pthread_mutex_t fileInfo_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t internFile_mutex = PTHREAD_MUTEX_INITIALIZER;

ConfigParser::ConfigParser() {
	// TODO Auto-generated constructor stub

}

ConfigParser::~ConfigParser() {
	// TODO Auto-generated destructor stub
}

bool ConfigParser::readInternalParamInt(const char* fileDirectory, const char* paramName, int* paramValue) {
	char paramStringValue[100];
	if (readInternalParam(fileDirectory, paramName, paramStringValue)) {
		*paramValue = atoi(paramStringValue);
		return true;
	}

	return false; // not found?
}
/**
 * Read internal parameter. File name is the same as parameter name. It's only one parameter in one file.
 * E.g. parameter range is saved in file "range.txt"
 */
bool ConfigParser::readInternalParam(const char* fileDirectory,
		const char* paramName, char* paramValue) {
	char temp[128];
	char param[128];
	FILE * hFile;

	sprintf(temp, "%s/%s.txt", fileDirectory, paramName);
	pthread_mutex_lock(&internFile_mutex);
	// open the file for reading
	hFile = fopen(temp, "r");

	if (hFile == NULL) {
#ifdef DEBUG_ERR_READING_FILEINFO
		Log::logErrMsg("Cannot open file: %s for reading. Err: %s", temp, strerror(errno));
#endif
		pthread_mutex_unlock(&internFile_mutex);
		return false;
	}

	int paramLength = getNextLine(hFile, param, 128); //new VtFileInfo(hFile);
	fclose(hFile);

	pthread_mutex_unlock(&internFile_mutex);
	if (paramLength > 0)
		strcpy(paramValue, param);
	return true;
}

bool ConfigParser::saveInternalParamInt(const char* fileDirectory,
		const char* paramName, int nValue) {
	char paramValue[10];
	sprintf(paramValue, "%d", nValue);
	return saveInternalParam(fileDirectory, paramName, paramValue);
}
/**
 * Save internal parameter. File name is the same as parameter name. It's only one parameter in one file.
 * E.g. parameter range is saved in file "range.txt"
 */
bool ConfigParser::saveInternalParam(const char* fileDirectory,
		const char* paramName, const char* paramValue) {
	char temp[300];
	FILE * hFileInfo;

	sprintf(temp, "%s/%s.txt", fileDirectory, paramName);

	pthread_mutex_lock(&internFile_mutex);
	hFileInfo = fopen(temp, "w");

	if (hFileInfo == NULL) {
		Log::logErrMsg("Cannot open file: %s for writing.", temp);
		pthread_mutex_unlock(&internFile_mutex);
		return false;
	}

	sprintf(temp, "%s\n", paramValue);
	fputs(temp, hFileInfo);
	fclose(hFileInfo);
	pthread_mutex_unlock(&internFile_mutex);
	return true;
}

bool ConfigParser::readConfig(const char* fileDirectory, const char* fileName) {
	char temp[128];
	FILE * hFile;

	sprintf(temp, "%s/%s", fileDirectory, fileName);
	pthread_mutex_lock(&fileInfo_mutex);
	// open the file for reading
	hFile = fopen(temp, "r");

	if (hFile == NULL) {
#ifdef DEBUG_ERR_READING_FILEINFO
		Log::logErrMsg("Cannot open file: %s for reading. Err: %s", temp, strerror(errno));
#endif
		pthread_mutex_unlock(&fileInfo_mutex);
		return false;
	}

	getInfoFromFile(hFile); //new VtFileInfo(hFile);
	fclose(hFile);

	pthread_mutex_unlock(&fileInfo_mutex);
	return true;
}

bool ConfigParser::saveOldConfig(const char* fileDirectory,
		const char* fileName) {
	char temp[300];
	FILE * hFileInfo;

	sprintf(temp, "%s/%s", fileDirectory, fileName);

	Log::logDbgMsg("Add new config: %s", temp);

	pthread_mutex_lock(&fileInfo_mutex);
	hFileInfo = fopen(temp, "w");

	if (hFileInfo == NULL) {
		Log::logErrMsg("Cannot open file: %s for writing.", temp);
		pthread_mutex_unlock(&fileInfo_mutex);
		return false;
	}

	fputs("***************************************\n", hFileInfo);
	fputs(CONFIG_COMMENT_VERSION, hFileInfo);
	fputs("***************************************\n", hFileInfo);

	sprintf(temp, "version=%s\n\n", DEFAULT_CONFIG_VERSION);//data->configVersion);
	fputs(temp, hFileInfo);

	fputs("***************************************\n", hFileInfo);
	fputs(CONFIG_COMMENT_IP, hFileInfo);
	fputs("***************************************\n", hFileInfo);
	sprintf(temp, "ip=%s\n\n", Data::getInstance()->dataGlobalt.ip);
	fputs(temp, hFileInfo);

	fputs("***************************************\n", hFileInfo);
	fputs(CONFIG_COMMENT_GAIN, hFileInfo);
	fputs("***************************************\n", hFileInfo);
	sprintf(temp, "gain=%d\n\n", Data::getInstance()->dataSignal.gain);
	fputs(temp, hFileInfo);

	fputs("***************************************\n", hFileInfo);
	fputs(CONFIG_COMMENT_TVG, hFileInfo);
	fputs("***************************************\n", hFileInfo);
	sprintf(temp, "tvg=%d\n\n", Data::getInstance()->dataSignal.tvg);
	fputs(temp, hFileInfo);

	fputs("***************************************\n", hFileInfo);
	fputs(CONFIG_COMMENT_FREQ, hFileInfo);
	fputs("***************************************\n", hFileInfo);
	sprintf(temp, "freq=%d\n\n", Data::getInstance()->dataSignal.freq);
	fputs(temp, hFileInfo);

	fputs("***************************************\n", hFileInfo);
	fputs(CONFIG_COMMENT_POW, hFileInfo);
	fputs("***************************************\n", hFileInfo);
	sprintf(temp, "pow=%d\n\n", Data::getInstance()->dataSignal.pow);
	fputs(temp, hFileInfo);

	fputs("***************************************\n", hFileInfo);
	fputs(CONFIG_COMMENT_ALARML, hFileInfo);
	fputs("***************************************\n", hFileInfo);
	sprintf(temp, "alarmL=%d\n\n", Data::getInstance()->dataSignal.alarmL);
	fputs(temp, hFileInfo);

	fputs("***************************************\n", hFileInfo);
	fputs(CONFIG_COMMENT_ALARMH, hFileInfo);
	fputs("***************************************\n", hFileInfo);
	sprintf(temp, "alarmH=%d\n\n", Data::getInstance()->dataSignal.alarmH);
	fputs(temp, hFileInfo);

	fputs("***************************************\n", hFileInfo);
	fputs(CONFIG_COMMENT_RANGE, hFileInfo);
	fputs("***************************************\n", hFileInfo);
	sprintf(temp, "range=%d\n\n", Data::getInstance()->dataSignal.range);
	fputs(temp, hFileInfo);

	fclose(hFileInfo);
	pthread_mutex_unlock(&fileInfo_mutex);
	return true;
}

/*
 bool VtFileInfoSaver::removeFileInfo(const char* fileDirectory,
 unsigned int destCommBox, unsigned int fileId) {
 char temp[128];
 sprintf(temp, "%s%u/%u", fileDirectory, destCommBox, fileId);
 pthread_mutex_lock(&fileInfo_mutex);
 remove(temp);
 pthread_mutex_unlock(&fileInfo_mutex);

 return true;
 }


 bool VtFileInfoSaver::moveIncommingToFinishedFolder(unsigned int commBox, unsigned int fileId) {
 char temp[300];
 FILE * hFileInfo;

 struct stat st;

 VtLogInterface* m_VtLogInterface = VtLogInterface::getInstance();

 sprintf(temp, "%s%u/", FILE_INCOMING_FINISHED_DIR, commBox);

 // create folder if not exist
 if (stat(temp, &st) != 0) {
 mkdir(temp, 0666);
 //printf("Created directory: %s", temp);
 }

 // open the file for writing
 sprintf(temp, "%s%u/%u", FILE_INCOMING_FINISHED_DIR, commBox, fileId);
 pthread_mutex_lock(&fileInfo_mutex);
 hFileInfo = fopen(temp, "w");

 if (hFileInfo == NULL) {
 m_VtLogInterface->logMsg(LOG_LEVELERROR, "Cannot save file: %s.", temp);
 pthread_mutex_unlock(&fileInfo_mutex);
 return false;
 }

 fclose(hFileInfo);
 pthread_mutex_unlock(&fileInfo_mutex);
 return true;
 }

 */
///////////////////////////////////////////////////////////
////				PRIVATE
///////////////////////////////////////////////////////////

// From file saved in waiting Queue "/var/fileQueue"
void ConfigParser::getInfoFromFile(FILE * hFile) {
	int nLineLength;
	char line[160];

	do {
		nLineLength = getNextLine(hFile, line, 160);
		//printf("New line: %s\n", line);
		if (nLineLength >= 0) {
			if (line[0] != '*')
				updateParameter(line);
		}
	} while (nLineLength >= 0);

}

void ConfigParser::updateParameter(char* line) {
	if (strlen(line) == 0) // empty line
		return;
	char* sepPointer = strstr(line, "=");
	if (sepPointer == NULL) {
		Log::logErrMsg("Wrong line in config file: %s", line);
		return;
	}
	int valuePos = sepPointer - line + 1;
	int nLength;
	char paramName[31];
	char paramValue[128];

	*sepPointer = 0; // null terminate paramName
	strcpy(paramName, line);
	strcpy(paramValue, &line[valuePos]);

	nLength = strlen(paramValue);

	//printf("Paramname: %s, value: %s.\n", paramName, paramValue);

	if (strcmp(paramName, "version") == 0) {
		// TODO: !!! WRONG: check config version and return if not matching
		strcpy(Data::getInstance()->configVersion, paramValue);
	} else if (strcmp(paramName, "ip") == 0) {
		Data::getInstance()->dataGlobalt.saveIp(paramValue);
	} else if (strcmp(paramName, "gain") == 0) {
		Data::getInstance()->dataSignal.saveGain(atoi(paramValue));
	} else if (strcmp(paramName, "tvg") == 0) {
		Data::getInstance()->dataSignal.saveTvg(atoi(paramValue));
	} else if (strcmp(paramName, "freq") == 0) {
		Data::getInstance()->dataSignal.saveFreq(atoi(paramValue));
	} else if (strcmp(paramName, "pow") == 0) {
		Data::getInstance()->dataSignal.savePow(atoi(paramValue));
	} else if (strcmp(paramName, "alarmL") == 0) {
		Data::getInstance()->dataSignal.saveAlarmL(atoi(paramValue));
	} else if (strcmp(paramName, "alarmH") == 0) {
		Data::getInstance()->dataSignal.saveAlarmH(atoi(paramValue));
	} else if (strcmp(paramName, "range") == 0) {
		Data::getInstance()->dataSignal.saveRange(atoi(paramValue));
	}
}

int ConfigParser::getNextLine(FILE * hFile, char* line, int maxToRead) {
	int c = 0;
	int i = -1;

	while (((c = fgetc(hFile)) != EOF) && (i < maxToRead - 1)) {
		i++;
		if (c == '\n')
			break;
		line[i] = c;
	}

	line[i] = 0;
	return i;
}

// return true if file exist
EnumConfigResult ConfigParser::existFile(const char* fileDirectory,
		const char* fileName) {
	char temp[128];
	FILE * hFile;
	struct stat st;

	// folder exist?
	if (stat(fileDirectory, &st) != 0) {
		return FOLDER_NOT_EXIST;
	}

	// try to open the file
	sprintf(temp, "%s/%s", fileDirectory, fileName);

	pthread_mutex_lock(&fileInfo_mutex);
	hFile = fopen(temp, "r");

	if (hFile == NULL) {
		pthread_mutex_unlock(&fileInfo_mutex);
		return FILE_NOT_EXIST;
	}
	fclose(hFile);
	pthread_mutex_unlock(&fileInfo_mutex);
	return CONFIG_OK;
}
