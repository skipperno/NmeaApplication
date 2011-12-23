/*
 * EchoDataWebSocket.cpp
 *
 *  Created on: Oct 4, 2011
 *      Author: ernad
 */

#include "EchoDataWebSocket.h"
#include "ServerConstants.h"

#include "Webserver.h"

#include "../data/Data.h"


unsigned char echoBuffer[LWS_SEND_BUFFER_PRE_PADDING + 1024 +
								  LWS_SEND_BUFFER_POST_PADDING];

unsigned char broadcastEchoMsg[2000];
int broadcastEchoLength = 0;

EchoDataWebSocket::EchoDataWebSocket() {
	// TODO Auto-generated constructor stub

}

EchoDataWebSocket::~EchoDataWebSocket() {
	// TODO Auto-generated destructor stub
}

/* dumb_increment protocol */

/*
 * one of these is auto-created for each connection and a pointer to the
 * appropriate instance is passed to the callback in the user parameter
 *
 * for this example protocol we use it to individualize the count for each
 * connection.
 */



int EchoDataWebSocket::callback_dumb_increment(struct libwebsocket_context * context,
			struct libwebsocket *wsi,
			enum libwebsocket_callback_reasons reason,
					       void *user, void *in, size_t len)
{
#ifdef DEBUG_WEBSERVER
	fprintf(stderr, "callback Data websocket, fd: %d, reason: %s\n", libwebsocket_get_socket_fd(wsi), ServerConstants::getCallbackReasonText(reason));
#endif
	int n;
	//unsigned char buf[LWS_SEND_BUFFER_PRE_PADDING + 512 +
		//				  LWS_SEND_BUFFER_POST_PADDING];
	//unsigned char *p = &buf[LWS_SEND_BUFFER_PRE_PADDING];
	struct sessionDataProtocol_1 *pss = (sessionDataProtocol_1 *)user;


	switch (reason) {

	case LWS_CALLBACK_ESTABLISHED:
#ifdef DEBUG_WEBSERVER
		fprintf(stdout, "********Data websocket established\n");
#endif
		break;

	/*
	 * in this protocol, we just use the broadcast action as the chance to
	 * send our own connection-specific data and ignore the broadcast info
	 * that is available in the 'in' parameter
	 */

	case LWS_CALLBACK_BROADCAST:
#ifdef DEBUG_WEBSERVER
		fprintf(stdout, "********Data websocket LWS_CALLBACK_BROADCAST\n");
#endif

		n = libwebsocket_write(wsi, &broadcastEchoMsg[LWS_SEND_BUFFER_PRE_PADDING], broadcastEchoLength, LWS_WRITE_TEXT);
#ifdef DEBUG_WEBSERVER
		fprintf(stdout, "** END **Data websocket LWS_CALLBACK_BROADCAST, length: %d\n", broadcastEchoLength);
#endif

		break;

	case LWS_CALLBACK_RECEIVE:
#ifdef DEBUG_WEBSERVER
		fprintf(stdout, "Data websocket LWS_CALLBACK_RECEIVE\n");
#endif
		fprintf(stderr, "rx %d\n", (int)len);
		if (len < 6)
			break;
		if (strcmp((char*)in, "reset\n") == 0)
			pss->number = 0;
		break;
	/*
	 * this just demonstrates how to use the protocol filter. If you won't
	 * study and reject connections based on header content, you don't need
	 * to handle this callback
	 */

	case LWS_CALLBACK_FILTER_PROTOCOL_CONNECTION:
		//dump_handshake_info((struct lws_tokens *)(long)user);
		/* you could return non-zero here and kill the connection */
		break;

	default:
#ifdef DEBUG_WEBSERVER
		fprintf(stderr, "!!! callback Data websocket, default case? Reason %d**********\n", (int)reason);
#endif
		break;
	}

	return 0;
}

void EchoDataWebSocket::broadcastMsgToClients(char* msg, int nLen) {
	libwebsocket_protocols* protoc = Webserver::getImplementedProtocols();
	echoBuffer[LWS_SEND_BUFFER_PRE_PADDING] = 'x';
	memcpy((char*)&broadcastEchoMsg[LWS_SEND_BUFFER_PRE_PADDING], msg, nLen);
	broadcastEchoLength = nLen;
	libwebsockets_broadcast(&protoc[PROTOCOL_DUMB_INCREMENT], &echoBuffer[LWS_SEND_BUFFER_PRE_PADDING], 1); //PROTOCOL_LWS_MIRROR = 2
#ifdef DEBUG_WEBSERVER
	printf("Broadcast ECHO %d bytes\n", nLen);
#endif
}
