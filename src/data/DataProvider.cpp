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
#include "../utility/NmeaMsgCreator.h"


#include "../json/elements.h"
using namespace json;

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

	ret = pthread_create(&threadDataProvider, NULL, runDataProvThread,
			(void*) this);
}

void * runDataProvThread(void *ptr) {
	DataProvider * dataProvider = (DataProvider *) ptr;

	char msgToSend[1000];
	Data* dataInstance = Data::getInstance();

	while (dataProvider->bRun) {
		////////////////////////////////////////////////////////
		// Send GPS, time, ... each second
		////////////////////////////////////////////////////////
		Data::getInstance()->getJsonTop(msgToSend);
		Dispatcher::sendConfigMsg(msgToSend, strlen(msgToSend));

		////////////////////////////////////////////////////////
		// Send DPT, DBS, ... each second if them are selected
		////////////////////////////////////////////////////////
		for (int sourceIndex = 0; sourceIndex < 5; sourceIndex++) {
			Array ioArray = Data::getInstance()->getOutputSettingsObject(sourceIndex);

			for (unsigned int i = 0; i < ioArray.Size(); i++) {
				String tempString = ioArray[i];
				if (strcmp(tempString.Value().c_str(), "a") == 0) {
					if (Data::getActiveDisplayIndex() == (sourceIndex + 1) && Data::getDisplayIoChoice() == 0) {
						NmeaMsgCreator::getDptMsgBuffer(msgToSend,
								dataInstance->getDepthTransMeters(), true,
								dataInstance->getSurfaceOffsetMeters(), true,
								0.f, false);
						Data::getInstance()->setNmeaMsg(msgToSend);
						//Dispatcher::sendConfigMsg(msgToSend, strlen(msgToSend));
					}
				} else if (strcmp(tempString.Value().c_str(), "b") == 0) {
					if (Data::getActiveDisplayIndex() == (sourceIndex + 1) && Data::getDisplayIoChoice() == 0) {
						NmeaMsgCreator::getDbsMsgBuffer(msgToSend,
								dataInstance->getDepthSurfaceMeters(), true,
								dataInstance->getDepthSurfaceFeet(), true,
								dataInstance->getDepthSurfaceFathoms(), true);
						Data::getInstance()->setNmeaMsg(msgToSend);
						//Dispatcher::sendConfigMsg(msgToSend, strlen(msgToSend));
					}
				} else if (strcmp(tempString.Value().c_str(), "c") == 0) {
					if (Data::getActiveDisplayIndex() == (sourceIndex + 1) && Data::getDisplayIoChoice() == 0) {
						NmeaMsgCreator::getDbtMsgBuffer(msgToSend,
								dataInstance->getDepthKeelMeters(), true,
								dataInstance->getDepthKeelFeet(), true,
								dataInstance->getDepthKeelFathoms(), true);
						Data::getInstance()->setNmeaMsg(msgToSend);
												//Dispatcher::sendConfigMsg(msgToSend, strlen(msgToSend));
					}
				} else if (strcmp(tempString.Value().c_str(), "d") == 0) {
					if (Data::getActiveDisplayIndex() == (sourceIndex + 1) && Data::getDisplayIoChoice() == 0) {
						NmeaMsgCreator::getDbkMsgBuffer(msgToSend,
								dataInstance->getDepthKeelMeters(), true,
								dataInstance->getDepthKeelFathoms(), true,
								dataInstance->getDepthKeelFathoms(), true);
						Data::getInstance()->setNmeaMsg(msgToSend);
												//Dispatcher::sendConfigMsg(msgToSend, strlen(msgToSend));
					}
				} else if (strcmp(tempString.Value().c_str(), "e") == 0) {
					if (Data::getActiveDisplayIndex() == (sourceIndex + 1) && Data::getDisplayIoChoice() == 0) {
						NmeaMsgCreator::getXdrMsgBuffer(msgToSend, 3.3, 5.5);
						Data::getInstance()->setNmeaMsg(msgToSend);
												//Dispatcher::sendConfigMsg(msgToSend, strlen(msgToSend));
					}
				}
			}
		}
		sleep(1);
	}
	return NULL;
}
