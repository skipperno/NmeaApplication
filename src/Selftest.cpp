/*
 * Selftest.cpp
 *
 *  Created on: Oct 31, 2011
 *      Author: ernad
 */

#include "Selftest.h"
#include "data/Data.h"
#include "MsgInHandler.h"
#include <string.h>

const char* TEST_A_GPIO = "18";
const char* TEST_B_GPIO = "19";

bool bRunTestThread = false;
int nTestSource = 0;

GpioCortex gpioCortexTestA;
GpioCortex gpioCortexTestB;

void* runTestThread(void *ptr);

Selftest::Selftest() {
	gpioCortexTestA.configureGpioAsOutput(TEST_A_GPIO);
	gpioCortexTestB.configureGpioAsOutput(TEST_B_GPIO);
}

Selftest::~Selftest() {
	// TODO Auto-generated destructor stub
}

void Selftest::startTest(int source) {


	bRunTestThread = true;
	nTestSource = source;
	pthread_create(&threadTest,   NULL, runTestThread, (void*) this);
}

void* runTestThread(void *ptr) {
	if (nTestSource == 0) {
		gpioCortexTestA.setOutputHigh(true);
		gpioCortexTestB.setOutputHigh(true);
	} else if (nTestSource == 1) {
		gpioCortexTestA.setOutputHigh(true);
	} else if (nTestSource == 2) {
		gpioCortexTestB.setOutputHigh(true);
	}

	usleep(10000); // give some time to rele

	while(bRunTestThread) {
		if(nTestSource == 0)
			MsgInHandler::getInstance()->sendMsgSerial1("$test,loopback,NMEA1*OK", strlen("$test,loopback,NMEA1*OK"));
		else if(nTestSource == 1)
			MsgInHandler::getInstance()->sendMsgSerial2("$test,loopback,NMEA2*OK", strlen("$test,loopback,NMEA2*OK"));
		else if(nTestSource == 2)
			MsgInHandler::getInstance()->sendMsgSerial3("$test,loopback,NMEA3*OK", strlen("$test,loopback,NMEA3*OK"));
		sleep(1);
	}
}


void Selftest::stopTest() {
	bRunTestThread = false;
	gpioCortexTestA.setOutputHigh(false);
	gpioCortexTestB.setOutputHigh(false);
}
