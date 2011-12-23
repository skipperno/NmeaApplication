/*
 * ServerConstants.h
 *
 *  Created on: Oct 4, 2011
 *      Author: ernad
 */

#ifndef SERVERCONSTANTS_H_
#define SERVERCONSTANTS_H_

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

class ServerConstants {

public:
	ServerConstants();
	virtual ~ServerConstants();

	static const char* getCallbackReasonText(int nReason);
};

#endif /* SERVERCONSTANTS_H_ */
