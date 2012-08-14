/*
 * DataProvider.cpp
 *
 *  Created on: Aug 30, 2011
 *      Author: ernad
 */
#include "../Selftest.h"

#include <string.h>
#include <stdio.h>

#include "DataProvider.h"
#include "Data.h"
#include "../comm/Dispatcher.h"
#include "../utility/NmeaMsgCreator.h"
#include "../webserver/DataWebSocket.h"
#include "Alarm.h"
#include "../utility/AlarmMsgCreator.h"

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
	sleep(5);
	printf("DATA PROVIDER START\n");
	int nActiveDisplay;

	while (dataProvider->bRun) {
		nActiveDisplay = Data::getInstance()->getActiveDisplayIndex();
		////////////////////////////////////////////////////////
		// Send GPS, time, ... each second
		////////////////////////////////////////////////////////
		Data::getInstance()->getJsonTop(msgToSend);
		DataWebSocket::broadcastMsgToClients(msgToSend, strlen(msgToSend));

		//	Dispatcher::sendConfigMsg(msgToSend, strlen(msgToSend));

		////////////////////////////////////////////////////////
		// Send DPT, DBS, ... each second if them are selected
		////////////////////////////////////////////////////////
		for (int sourceIndex = 0; sourceIndex < 2; sourceIndex++) { //TODO: it's only for COM1 and COM 2. We needs for ethernet and CAN?
			Array ioArray = Data::getInstance()->getOutputSettingsObject(sourceIndex);
			int nArray[5];
			Number tempNumber;

			for (unsigned int i = 0; i<5;i++){
				tempNumber = ioArray[i];
				nArray[i] = tempNumber.Value();
			}
			if (nActiveDisplay == sourceIndex) {
				//for (unsigned int i = 0; i < ioArray.Size(); i++) {
				//	String tempString = ioArray[i];

					if (nArray[0] == 1) {
						if (Data::getInstance()->getDisplayIoChoice()
										== 0) {
							NmeaMsgCreator::getDptMsgBuffer(msgToSend,
									dataInstance->getDepthTransMeters(), true,
									dataInstance->getSurfaceOffsetMeters(),
									true, 0.f, false);
							Data::getInstance()->sendNmeaMsg(msgToSend,
									NMEA_DIRECT_OUT);
							//Dispatcher::sendConfigMsg(msgToSend, strlen(msgToSend));
						}
					}
					if (nArray[1] == 1) {
						if (Data::getInstance()->getDisplayIoChoice() == 0) {
							NmeaMsgCreator::getDbsMsgBuffer(msgToSend,
									dataInstance->getDepthSurfaceMeters(),
									true, dataInstance->getDepthSurfaceFeet(),
									true,
									dataInstance->getDepthSurfaceFathoms(),
									true);
							Data::getInstance()->sendNmeaMsg(msgToSend,
									NMEA_DIRECT_OUT);
							//Dispatcher::sendConfigMsg(msgToSend, strlen(msgToSend));
						}
					}
					if (nArray[2] == 1) {
						if (Data::getInstance()->getDisplayIoChoice() == 0) {
							NmeaMsgCreator::getDbtMsgBuffer(msgToSend,
									dataInstance->getDepthKeelMeters(), true,
									dataInstance->getDepthKeelFeet(), true,
									dataInstance->getDepthKeelFathoms(), true);
							Data::getInstance()->sendNmeaMsg(msgToSend,
									NMEA_DIRECT_OUT);
							//Dispatcher::sendConfigMsg(msgToSend, strlen(msgToSend));
						}
					}
					if (nArray[3] == 1) {
						if (Data::getInstance()->getDisplayIoChoice() == 0) {
							NmeaMsgCreator::getDbkMsgBuffer(msgToSend,
									dataInstance->getDepthKeelMeters(), true,
									dataInstance->getDepthKeelFathoms(), true,
									dataInstance->getDepthKeelFathoms(), true);
							Data::getInstance()->sendNmeaMsg(msgToSend,
									NMEA_DIRECT_OUT);
							//Dispatcher::sendConfigMsg(msgToSend, strlen(msgToSend));
						}
					}
					if (nArray[4] == 1) {
						if (Data::getInstance()->getDisplayIoChoice() == 0) {
							NmeaMsgCreator::getXdrMsgBuffer(msgToSend, 3.3, 5.5);
							Data::getInstance()->sendNmeaMsg(msgToSend,
									NMEA_DIRECT_OUT);
							//Dispatcher::sendConfigMsg(msgToSend, strlen(msgToSend));
						}
					}
				//}
			}
			if (nActiveDisplay > -1 && Data::getInstance()->isAlarmMsgEnabled(nActiveDisplay)) {
						AlarmMsgCreator::getAlarmMsgBuffer(msgToSend,
								Alarm::getAlarmSenderId(),
								Data::getInstance()->getDepthTransMeters(),
								Alarm::isAlarmState(), Alarm::isConfirmed());
						Data::getInstance()->sendNmeaMsg(msgToSend, NMEA_DIRECT_OUT);
					}
		}



		sleep(1);
	}
	return NULL;
}
