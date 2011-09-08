/*
 * DataProvider.h
 *
 *  Created on: Aug 30, 2011
 *      Author: ernad
 */

#ifndef DATAPROVIDER_H_
#define DATAPROVIDER_H_

#include <sys/types.h>
#include <pthread.h>

class DataProvider {
public:
	DataProvider();
	virtual ~DataProvider();
	void startDataProvider();
	bool bRun;

private:
	pthread_t threadDataProvider;

};

#endif /* DATAPROVIDER_H_ */
