/*
 * SignalGenerator.h
 *
 *  Created on: Aug 24, 2010
 *      Author: root
 */

#ifndef SIGNALGENERATOR_H_
#define SIGNALGENERATOR_H_

#define MAX_SIGNAL_GROUPS   5

#include <semaphore.h>
#include <pthread.h>
#include "LinkedList.h"

class ESignal;

class SignalGenerator {
public:
	SignalGenerator(const char* semName);
	virtual ~SignalGenerator();

	void addSignal(ESignal* eSignal);
	ESignal* waitOnSignal();

	static SignalGenerator* getInstance(int nIndex);

	static bool signalGeneratorInitialized[MAX_SIGNAL_GROUPS];

	pthread_mutex_t myMutex;
	pthread_mutex_t* pJob_queue_mutex;
private:

	sem_t* pJob_queue_count;  // A semaphore counting the number of jobs in the queue.

	LinkedList linkedList;
	char semaphoreName[30];
};

#endif /* SIGNALGENERATOR_H_ */
