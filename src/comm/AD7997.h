/*
 * AD7997.h
 *
 *  Created on: Oct 21, 2011
 *      Author: ernad
 */

#ifndef AD7997_H_
#define AD7997_H_

#include "GpioCortex.h"
#include <sys/types.h>
#include <pthread.h>

class AD7997 {
public:
	AD7997();
	virtual ~AD7997();

	void startMeasuringAD7997(void);
	void configureConversionAllCh(int file);

	int i2c_write_1b(int fd, unsigned char buf);
	int i2c_write_2b(int fd, unsigned char buf[2]);
	int i2c_write_3b(int fd, unsigned char buf[3]);
	void runThreadImplementation(void);

private:
	GpioCortex gpioCortex;
	pthread_t threadMeasur;

};

#endif /* AD7997_H_ */
