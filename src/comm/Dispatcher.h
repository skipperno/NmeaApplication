/*
 * Dispatcher.h
 *
 *  Created on: Jun 27, 2011
 *      Author: ernad
 */

#ifndef DISPATCHER_H_
#define DISPATCHER_H_

#include <map>
using namespace std;


#include "SocketClientPipe.h"

class Dispatcher {
public:
	Dispatcher();
	virtual ~Dispatcher();
	static void sendEchoMsg(const void *vptr, size_t nSize);
	static void sendConfigMsg(const void *vptr, size_t nSize);
	static void addClient(SocketClientPipe* socketClientPipe, socktType type);
	static void onDisconnected(SocketClientPipe* disconnetdClientPipe);
private:

};

#endif /* DISPATCHER_H_ */
