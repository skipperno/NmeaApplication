/*
 * ServerPublic.h
 *
 *  Created on: Sep 30, 2011
 *      Author: ernad
 */

#ifndef SERVERPUBLIC_H_
#define SERVERPUBLIC_H_

#include "Webserver.h"
#include "DataWebSocket.h"

/////////////////////////////////////////////////////////////////
// session can be used to save some info about this user
// Callback has pointer to this session as paremaeter "user"
/////////////////////////////////////////////////////////////////

struct sessionDataProtocol_1 {
	int number;
};

struct sessionDataProtocol_2 {
	struct libwebsocket *wsi;
	int ringbuffer_tail;
};

enum demo_protocols {
	/* always first */
	PROTOCOL_HTTP = 0,

	PROTOCOL_DUMB_INCREMENT,
	PROTOCOL_LWS_MIRROR,

	/* always last */
	DEMO_PROTOCOL_COUNT
};



#endif /* SERVERPUBLIC_H_ */
