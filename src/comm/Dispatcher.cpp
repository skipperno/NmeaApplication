/*
 * Dispatcher.cpp
 *
 *  Created on: Jun 27, 2011
 *      Author: ernad
 */

#include "Dispatcher.h"
#include <stdio.h>

map<unsigned int, SocketClientPipe*> socketDispatcherEchoData;
map<unsigned int, SocketClientPipe*> socketDispatcherConfigData;

int dummi = 0;

pthread_mutex_t dispatcher_mutex;

Dispatcher::Dispatcher() {
	// TODO Auto-generated constructor stub

}

Dispatcher::~Dispatcher() {
	// TODO Auto-generated destructor stub
}

void Dispatcher::sendEchoMsg(const void *vptr, size_t nSize) {
	map<unsigned int, SocketClientPipe*>::iterator socketIterator;
	SocketClientPipe* socketClientPipe;
	int clientsCount = 0;

	for (socketIterator = socketDispatcherEchoData.begin(); socketIterator
			!= socketDispatcherEchoData.end();) {
		socketClientPipe = (*socketIterator).second;
		socketClientPipe->socketClientPipe_send(vptr, nSize);
		socketIterator++;
		clientsCount++;
	}

	if (clientsCount == 0) {
		//printf("ALARM DISPLAY\n");
	}
}

void Dispatcher::sendConfigMsg(const void *vptr, size_t nSize) {
/*	pthread_mutex_lock(&dispatcher_mutex);

	map<unsigned int, SocketClientPipe*>::iterator socketIterator;
	SocketClientPipe* socketClientPipe;
	int clientsCount = 0;

	for (socketIterator = socketDispatcherConfigData.begin(); socketIterator
			!= socketDispatcherConfigData.end();) {
		socketClientPipe = (*socketIterator).second;
		if(socketClientPipe->socketClientPipe_send(vptr, nSize) <= 0) {
			onDisconnected(socketClientPipe);
		}
		socketIterator++;
		clientsCount++;
	}

	pthread_mutex_unlock(&dispatcher_mutex);

	if (clientsCount == 0) {
		//printf("ALARM DISPLAY\n");
	}*/
}

void Dispatcher::addClient(SocketClientPipe* socketClientPipe, socktType type) {
	if (type == SOCK_ECHO)
		socketDispatcherEchoData[dummi++] = socketClientPipe;
	else
		socketDispatcherConfigData[dummi++] = socketClientPipe;
}

void Dispatcher::onDisconnected(SocketClientPipe* disconnetdClientPipe) {
	map<unsigned int, SocketClientPipe*>::iterator socketIterator;
	SocketClientPipe* socketClientPipe;
	for (socketIterator = socketDispatcherEchoData.begin(); socketIterator
			!= socketDispatcherEchoData.end();) {
		socketClientPipe = (*socketIterator).second;
		if (disconnetdClientPipe == socketClientPipe) {
			socketDispatcherEchoData.erase((*socketIterator).first);
			return;
		} else {
			socketIterator++;
		}
	}

	for (socketIterator = socketDispatcherConfigData.begin(); socketIterator
				!= socketDispatcherConfigData.end();) {
			socketClientPipe = (*socketIterator).second;
			if (disconnetdClientPipe == socketClientPipe) {
				socketDispatcherConfigData.erase((*socketIterator).first);
				return;
			} else {
				socketIterator++;
			}
		}
}
