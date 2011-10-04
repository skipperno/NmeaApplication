/*
 * Webserver.h
 *
 *  Created on: Sep 29, 2011
 *      Author: ernad
 */

#ifndef WEBSERVER_H_
#define WEBSERVER_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <sys/time.h>

#include "MimeTypes.h"
#include "DataWebSocket.h"
#include "EchoDataWebSocket.h"

#include "../data/Data.h"
/*
unsigned char dataMsg[1000];
int dataLength = 0;
unsigned char broadcastMsg[1300];
int broadcastLength = 0;
*/
//#include "../lib/libwebsockets.h"
extern "C" {
//#include <libwebsockets.h>
#include "../lib/libwebsockets.h"
}


class Webserver {
public:
	Webserver();
	virtual ~Webserver();
	int mainLoop();
	static libwebsocket_protocols* getImplementedProtocols();

	static int callback_http(struct libwebsocket_context * context,
			struct libwebsocket *wsi,
			enum libwebsocket_callback_reasons reason, void *user,
								   void *in, size_t len);
	static int callback_dumb_increment(struct libwebsocket_context * context,
				struct libwebsocket *wsi,
				enum libwebsocket_callback_reasons reason,
						       void *user, void *in, size_t len);
};

#endif /* WEBSERVER_H_ */
