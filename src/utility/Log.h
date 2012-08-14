/*
 * Log.h
 *
 *  Created on: Feb 8, 2012
 *      Author: ernad
 */

#ifndef LOG_H_
#define LOG_H_

class Log {
public:
	Log();
	virtual ~Log();

	static void logDbgMsg(const char* msg, ...);
	static void logErrMsg(const char* msg, ...);
};

#endif /* LOG_H_ */
