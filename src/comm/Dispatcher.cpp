/*
 * Dispatcher.cpp
 *
 *  Created on: Jun 27, 2011
 *      Author: ernad
 */

#include "Dispatcher.h"
#include <stdio.h>

map<unsigned int, SocketClientPipe*> socketDispatcherMap;
int dummi = 0;

Dispatcher::Dispatcher() {
	// TODO Auto-generated constructor stub

}

Dispatcher::~Dispatcher() {
	// TODO Auto-generated destructor stub
}

void Dispatcher::sendMsg(const void *vptr, size_t nSize) {
	map<unsigned int, SocketClientPipe*>::iterator socketIterator;
	SocketClientPipe* socketClientPipe;
	int clientsCount = 0;

	for (socketIterator = socketDispatcherMap.begin(); socketIterator
			!= socketDispatcherMap.end();) {
		socketClientPipe = (*socketIterator).second;
		socketClientPipe->socketClientPipe_send(vptr, nSize);
		socketIterator++;
		clientsCount++;
	}

	if (clientsCount == 0) {
		printf("ALARM DISPLAY\n");
	}
}

void Dispatcher::addClient(SocketClientPipe* socketClientPipe) {
	socketDispatcherMap[dummi++] = socketClientPipe;
}

void Dispatcher::onDisconnected(SocketClientPipe* disconnetdClientPipe) {
	map<unsigned int, SocketClientPipe*>::iterator socketIterator;
	SocketClientPipe* socketClientPipe;
	for (socketIterator = socketDispatcherMap.begin(); socketIterator
			!= socketDispatcherMap.end();) {
		socketClientPipe = (*socketIterator).second;
		if (disconnetdClientPipe == socketClientPipe) {
			socketDispatcherMap.erase((*socketIterator).first);
			return;
		} else {
			socketIterator++;
		}
	}
}
