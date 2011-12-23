/*
 * GpioCortex.h
 *
 *  Created on: Oct 25, 2011
 *      Author: ernad
 */

#ifndef GPIOCORTEX_H_
#define GPIOCORTEX_H_

class GpioCortex {
public:
	GpioCortex();
	virtual ~GpioCortex();
	int configureGpioAsOutput(const char* ioPinName);
	int setOutputHigh(bool bHigh);

private:
	char ioPin[4];
};

#endif /* GPIOCORTEX_H_ */
