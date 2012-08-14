/*
 * Log.cpp
 *
 *  Created on: Feb 8, 2012
 *      Author: ernad
 */

#include "Log.h"

#include <unistd.h>
#include <pthread.h>
#include <stdio.h> //va_list
#include <stdarg.h> //va_start & va_end

Log::Log() {
	// TODO Auto-generated constructor stub

}

Log::~Log() {
	// TODO Auto-generated destructor stub
}

void Log::logDbgMsg(const char* msg, ...) {  // TODO: !!!error if length > 800
	char logMessage[800]; // must have place for all characters
	va_list args;
	//pthread_mutex_lock(&log_mutex);

	///////////////////////////////////////////
	// TAKE RECEIVED ARGUMENTS AND FORMATED MSG
	va_start(args, msg);
	// Copy arguments to "logMessage"
	vsprintf(logMessage, msg, args);

	va_end(args);
	///////////////////////////////////////////

	printf("DEBUG: %s\n", logMessage);
}

void Log::logErrMsg(const char* msg, ...) { // TODO: !!!error if length > 800
	char logMessage[800]; // must have place for all characters
		va_list args;
		//pthread_mutex_lock(&log_mutex);

		///////////////////////////////////////////
		// TAKE RECEIVED ARGUMENTS AND FORMATED MSG
		va_start(args, msg);
		// Copy arguments to "logMessage"
		vsprintf(logMessage, msg, args);

		va_end(args);
	printf("ERROR: %s\n", logMessage);
}
