/*
 * DataWebSocket.h
 *
 *  Created on: Sep 30, 2011
 *      Author: ernad
 */

#ifndef DATAWEBSOCKET_H_
#define DATAWEBSOCKET_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <sys/time.h>

#include "MimeTypes.h"


extern "C" {
//#include <libwebsockets.h>
#include "../lib/libwebsockets.h"
}

class DataWebSocket {
public:
	DataWebSocket();
	virtual ~DataWebSocket();

	static int callbackDataWebSocket(struct libwebsocket_context * context,
			struct libwebsocket *wsi,
			enum libwebsocket_callback_reasons reason,
					       void *user, void *in, size_t len);

	static void broadcastMsgToClients(char* msg, int nLen);
};

#endif /* DATAWEBSOCKET_H_ */
