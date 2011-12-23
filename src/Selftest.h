/*
 * Selftest.h
 *
 *  Created on: Oct 31, 2011
 *      Author: ernad
 */

#ifndef SELFTEST_H_
#define SELFTEST_H_

#include "comm/GpioCortex.h"
#include <pthread.h>

class Selftest {
public:
	Selftest();
	virtual ~Selftest();

	void startTest(int source);
	void stopTest();

	pthread_t threadTest;
private:

};

#endif /* SELFTEST_H_ */
