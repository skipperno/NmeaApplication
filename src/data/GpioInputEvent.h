/*
 * GpioInputEvent.h
 *
 *  Created on: Jan 25, 2012
 *      Author: ernad
 */

#ifndef GPIOINPUTEVENT_H_
#define GPIOINPUTEVENT_H_

#include <pthread.h>

class GpioCortex;


class GpioInputEvent {
public:
	GpioInputEvent();
	virtual ~GpioInputEvent();
	void runGpioEventHandler();
	void callbackGpioEvent(int eventArrayIndex);
private:
	GpioCortex* pGpioCortex;
	pthread_t threadGpio;
};

#endif /* GPIOINPUTEVENT_H_ */
