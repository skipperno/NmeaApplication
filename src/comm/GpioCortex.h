/*
 * GpioCortex.h
 *
 *  Created on: Oct 25, 2011
 *      Author: ernad
 */

#ifndef GPIOCORTEX_H_
#define GPIOCORTEX_H_

class GpioInputEvent;

class GpioCortex {
public:
	GpioCortex();
	GpioCortex(const char* ioPinName);
	GpioCortex(unsigned char* gpioPins, int nCount);
	virtual ~GpioCortex();
	int configureGpioAsOutput(const char*   ioPinName);
	int configureGpioAsInput (unsigned char ioPinName);
	int setOutputHigh(bool bHigh);
	int waitOnEdgeEvent(GpioInputEvent* gpioInputEvent);
private:
	int configureGpioAsOutput(unsigned char ioPinName);
	int setRisingEdge(unsigned char ioPinName, bool bRising);

private:
	char ioPin[4];
	char ioPinsArray[100];
	int nPinCount;
};

#endif /* GPIOCORTEX_H_ */
