/*
 * EchoDataWebSocket.h
 *
 *  Created on: Oct 4, 2011
 *      Author: ernad
 */

#ifndef ECHODATAWEBSOCKET_H_
#define ECHODATAWEBSOCKET_H_


#include "../data/Data.h"
#include "ServerPublic.h"

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
