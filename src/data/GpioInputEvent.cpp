/*
 * GpioInputEvent.cpp
 *
 *  Created on: Jan 25, 2012
 *      Author: ernad
 */

#include "GpioInputEvent.h"

#include <stdio.h>
#include "../comm/GpioCortex.h"
#include "Alarm.h"

//const char* EXT_RESET = "117"; // PXA310
//const char* EXT_RESET = "115"; // PXA320

//unsigned char eventPinArray = {42, 101, 43, 117}; // PXA310
unsigned char eventPinArray[] = {5, 99, 53, 115};   // PXA320 (SPARE I1, SPARE I2, SPARE I3, EXT_RESET)
const char* eventPinNameArray[] = {"SPARE I1", "SPARE I2", "SPARE I3", "EXT_RESET"};

void * runGpioEventThread(void *ptr);

GpioInputEvent::GpioInputEvent() {
	pGpioCortex = new GpioCortex(eventPinArray, 4);
	pthread_create(&threadGpio,   NULL, runGpioEventThread, (void*) this);
}

GpioInputEvent::~GpioInputEvent() {
	// TODO Auto-generated destructor stub
}

void * runGpioEventThread(void *ptr) {

	((GpioInputEvent*)ptr)->runGpioEventHandler(); // !!! Blocking function
	return 0;
}

void GpioInputEvent::runGpioEventHandler() {
	pGpioCortex->waitOnEdgeEvent(this); // blocking function
}

void GpioInputEvent::callbackGpioEvent(int eventArrayIndex) {
	printf("GPIO EVENT ON: %s\n", eventPinNameArray[eventArrayIndex]);
	if (eventArrayIndex == 3) { // EXTERNAL_RESET
		Alarm::confirmAlarm();
	}
}

