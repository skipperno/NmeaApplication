/*
 * SignalGenerator.cpp
 *
 *  Created on: Aug 24, 2010
 *      Author: root
 */

#include "SignalGenerator.h"
#include <malloc.h>
#include "ESignal.h"
#include "EByteArray.h"

#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#include <fcntl.h>


SignalGenerator* signalGeneratorInstance [MAX_SIGNAL_GROUPS];
bool SignalGenerator::signalGeneratorInitialized[MAX_SIGNAL_GROUPS] ={false, false, false, false, false};
//bool signalGeneratorInitialized = false;
pthread_mutex_t constructorMutex;

SignalGenerator::SignalGenerator(const char* semName) {
	printf("***Creating instance of SignalGenerator: %s\n", semName);
	strcpy(this->semaphoreName, semName);
	pJob_queue_mutex = &myMutex;
	pthread_mutex_init (pJob_queue_mutex, NULL);
	sem_unlink (semaphoreName);
	pJob_queue_count = sem_open(semaphoreName, O_CREAT, 0644, 0);
	if (pJob_queue_count == SEM_FAILED) {
		printf("Critical, cannot open semaphore\n");//TODO
	}
}

SignalGenerator::~SignalGenerator() {
	sem_unlink (semaphoreName);
	sem_close(pJob_queue_count);
}

SignalGenerator* SignalGenerator::getInstance(int nIndex) {
	char semName[30];
	pthread_mutex_lock(&constructorMutex);
	if (!signalGeneratorInitialized[nIndex]) {
		sprintf(semName, "SigGenerator_%d", nIndex);

		signalGeneratorInstance[nIndex] = new SignalGenerator(semName);

		signalGeneratorInitialized[nIndex] = true;
	}
	pthread_mutex_unlock(&constructorMutex);
	return signalGeneratorInstance[nIndex];
}

void SignalGenerator::addSignal(ESignal* eSignal) {
#ifdef DEBUG_SIGNALGENERATOR
	printf("1 --> addSignal list: %s\n", semaphoreName);
#endif

	pthread_mutex_lock(pJob_queue_mutex); //&job_queue_mutex);
	linkedList.enque(eSignal);

	sem_post(pJob_queue_count); //&job_queue_count);
	pthread_mutex_unlock(pJob_queue_mutex); //&job_queue_mutex);
#ifdef DEBUG_SIGNALGENERATOR
	printf("1  addSignal finish, id: %s\n", semaphoreName);
#endif
}

ESignal* SignalGenerator::waitOnSignal() {
	ESignal* eSignal = NULL;
#ifdef DEBUG_SIGNALGENERATOR
	printf("1 ** start waitOnSignal list: %s, size: %u\n", semaphoreName, linkedList.size());
#endif


	sem_wait(pJob_queue_count);//&job_queue_count);
	pthread_mutex_lock(pJob_queue_mutex); //&job_queue_mutex);
	eSignal = (ESignal*)linkedList.deque();
	pthread_mutex_unlock(pJob_queue_mutex); //&job_queue_mutex);
#ifdef DEBUG_SIGNALGENERATOR
	printf("1 finish waitOnSignal: %s\n", semaphoreName);
#endif
	return eSignal;
}

