/*
 * DataGlobalt.h
 *
 *  Created on: Mar 15, 2012
 *      Author: ernad
 */

#ifndef DATAGLOBALT_H_
#define DATAGLOBALT_H_

#include "../json/elements.h"
using namespace json;

class DataGlobalt {
public:
	DataGlobalt();
	virtual ~DataGlobalt();

	void init();
	void updateObjectWithJson(Object json);
	void objectToJsonMsg(char* jsonMsg);

	void saveIp(const char* newValue);
	void saveBaudCom1(int newValue);
	void saveBaudCom2(int newValue);
	void saveBaudCom3(int newValue);

	char ip[16];
	int baudCom1;
	int baudCom2;
	int baudCom3;

private:
	// used when reading config file
	void setIp(const char* gainStr);
	void setBaudCom1(const char* newValue);
	void setBaudCom2(const char* newValue);
	void setBaudCom3(const char* newValue);
};

#endif /* DATAGLOBALT_H_ */
