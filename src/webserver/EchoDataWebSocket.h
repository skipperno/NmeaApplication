/*
 * EchoDataWebSocket.h
 *
 *  Created on: Oct 4, 2011
 *      Author: ernad
 */

#ifndef ECHODATAWEBSOCKET_H_
#define ECHODATAWEBSOCKET_H_


//#include "../data/Data.h"
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


class EchoDataWebSocket {
public:
	EchoDataWebSocket();
	virtual ~EchoDataWebSocket();

	static int callback_dumb_increment(struct libwebsocket_context * context,
			struct libwebsocket *wsi, enum libwebsocket_callback_reasons reason,
					       void *user, void *in, size_t len);

	static void broadcastMsgToClients(char* msg, int nLen);

private:

};

#endif /* ECHODATAWEBSOCKET_H_ */
