/*
 * FileAccess.cpp
 *
 *  Created on: Feb 8, 2012
 *      Author: ernad
 */

#include "FileAccess.h"
#include "../utility/Log.h"

#include <sys/stat.h>
#include <errno.h>
#include <pthread.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../utility/SysTime.h"
#include "Data.h"

static pthread_mutex_t file_mutex = PTHREAD_MUTEX_INITIALIZER;
int nOldHour = -1;

char currentHourString[] = { "\0\0\0" }; // changed after the first time reading
char currentDate[] = { "\0\0\0\0\0\0\0\0\0" }; // changed after the first time reading
char mainSavingDirectory[] = { "/media/mySD" };
bool transducerSettingsChanged = false;
char logVersion[] = { "1.01" };

FileAccess::FileAccess() {
	// TODO Auto-generated constructor stub

}

FileAccess::~FileAccess() {
	// TODO Auto-generated destructor stub
}

void FileAccess::notifySettingsChanged() {
	transducerSettingsChanged = true;
}

bool FileAccess::addBottomMsg(int nBottom) {
	FILE * pFile;
	char timeString[10];
	char dateString[9];
	char lineMsg[500];
	char tempString[100];
	bool bWritingNewFile = false;
	//char settingsString[40];

	int nNewHour = SysTime::minutSecondToString(timeString);
	if (nOldHour != nNewHour || currentHourString[0] == 0) {
		nOldHour = nNewHour;
		sprintf(currentHourString, "%.2d", nNewHour);

		SysTime::sysDate_toStringNotSeparator(dateString);

		if (strcmp(dateString, currentDate) != 0) {
			strcpy(currentDate, dateString);
			sprintf(tempString, "%s/%s", mainSavingDirectory, currentDate);
			createDirectoryIfNotExist(tempString);
		}

		bWritingNewFile = true;
	}

	sprintf(tempString, "%s/%s/%s", mainSavingDirectory, currentDate,
			currentHourString);



	// open the file for writing
	pthread_mutex_lock(&file_mutex);
	pFile = fopen(tempString, "a");

	if (pFile == NULL) {
		Log::logErrMsg("Cannot open file: %s for writing.", tempString);
		pthread_mutex_unlock(&file_mutex);
		return false;
	}

	if (bWritingNewFile || transducerSettingsChanged) { // start of new file or changed settings. Write this info to file
		sprintf(lineMsg, "Logging version %s, tab separated\n", logVersion);
		fwrite(lineMsg, 1, strlen(lineMsg), pFile);

		fwrite("time\tbootom\tlat\tlon\talarmSh\talarmDeep\trange\tgain\ttvg\n", 1, strlen("time\tbootom\tlat\tlon\talarmSh\talarmDeep\trange\tgain\ttvg\n"), pFile);

		transducerSettingsChanged = false;
		/*getSettingsAsString(settingsString);
		fwrite(settingsString, 1, strlen(settingsString), pFile);*/
	}

	Data* data = Data::getInstance();
	sprintf(lineMsg, "%s\t%s\t%s\t%d\t%d\t%d\t%d\t%d\t%d\n", timeString,
			data->getLat(), data->getLon(),
			nBottom,
			data->getAlarmL(), data->getAlarmH(),
			data->getRange(),
			data->getGain(), data->getTvg());
	//getVelocity

	fwrite(lineMsg, 1, strlen(lineMsg), pFile);
	//fputs(temp, hFileInfo); // if string

	fclose(pFile);
	pthread_mutex_unlock(&file_mutex);
	return true;
}

void FileAccess::getSettingsAsString(char* msg) {
	Data* data = Data::getInstance();
	sprintf(msg, "R:%d, G:%d, T:%d\n", data->getRange(), data->getGain(),
			data->getTvg());
}

bool FileAccess::createDirectoryIfNotExist(const char* newDirectory) {
	struct stat st;

	if (stat(newDirectory, &st) != 0) {
		mkdir(newDirectory, 0644);
	}
	return true;
}

bool FileAccess::addMsg(const char* mainDirectory, const char* fileName,
		const char* msg, int nMsgLength) {
	char filePath[100];
	FILE * pFile;

	struct stat st;

	sprintf(filePath, "%s/%s", mainDirectory, fileName);

	///////////////////////////////////

	// create folder if not exist
	if (stat(mainDirectory, &st) != 0) {
		mkdir(mainDirectory, 0644);
	}

	// open the file for writing
	pthread_mutex_lock(&file_mutex);
	pFile = fopen(filePath, "a");

	if (pFile == NULL) {
		Log::logErrMsg("Cannot open file: %s for writing.", filePath);
		pthread_mutex_unlock(&file_mutex);
		return false;
	}

	fwrite(msg, 1, nMsgLength, pFile);
	//fputs(temp, hFileInfo); // if string

	fclose(pFile);
	pthread_mutex_unlock(&file_mutex);
	return true;
}
