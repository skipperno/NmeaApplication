/*
 * DataProvider.cpp
 *
 *  Created on: Aug 30, 2011
 *      Author: ernad
 */

#include <string.h>
#include <stdio.h>

#include "DataProvider.h"
#include "Data.h"
#include "../comm/Dispatcher.h"




void * runDataProvThread(void *ptr);

DataProvider::DataProvider() {
	// TODO Auto-generated constructor stub
	bRun = true;
}

DataProvider::~DataProvider() {
	// TODO Auto-generated destructor stub
}

void DataProvider::startDataProvider() {
	int ret;

	ret = pthread_create(&threadDataProvider, NULL, runDataProvThread, (void*) this);
}

void * runDataProvThread(void *ptr) {
	DataProvider * dataProvider = (DataProvider *)ptr;

	char msgToSend[1000];

	while(dataProvider->bRun){
		Data::getInstance()->getJsonTop(msgToSend);
		Dispatcher::sendConfigMsg(msgToSend, strlen(msgToSend));
		sleep(1);
	}
	return NULL;
}
