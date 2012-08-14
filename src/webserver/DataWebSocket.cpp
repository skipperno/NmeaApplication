/*
 * DataWebSocket.cpp
 *
 *  Created on: Sep 30, 2011
 *      Author: ernad
 */

#include "DataWebSocket.h"
#include "ServerConstants.h"
#include "Webserver.h"

#include "../data/Data.h"




unsigned char dataMsg[1000];
int dataLength = 0;
unsigned char broadcastMsg[1300];
int broadcastLength = 0;



DataWebSocket::DataWebSocket() {
	// TODO Auto-generated constructor stub

}

DataWebSocket::~DataWebSocket() {
	// TODO Auto-generated destructor stub
}

int DataWebSocket::callbackDataWebSocket(struct libwebsocket_context * context,
		struct libwebsocket *wsi,
		enum libwebsocket_callback_reasons reason,
				       void *user, void *in, size_t len){
#ifdef DEBUG_WEBSERVER
	fprintf(stderr, "*****callback Mirror, fd: %d, reason: %s\n", libwebsocket_get_socket_fd(wsi), ServerConstants::getCallbackReasonText(reason));
#endif

			int n;
			// DON'T REMOVE THIS, can be used as session
			// struct sessionDataProtocol_2 *pss = (sessionDataProtocol_2 *)user;


			switch (reason) {

			case LWS_CALLBACK_ESTABLISHED:
#ifdef DEBUG_WEBSERVER
				fprintf(stdout, "**********Mirror established\n");
		#endif
				/*pss->ringbuffer_tail = ringbuffer_head;
				pss->wsi = wsi;*/
				break;

			case LWS_CALLBACK_SERVER_WRITEABLE: // notified that you can write to this socket without blocking
		#ifdef DEBUG_WEBSERVER
				fprintf(stdout, "Mirror CALLBACK_SERVER_WRITEABLE, %d\n", (int)wsi);
		#endif
				//fprintf(stdout, "Mirror CALLBACK_SERVER_WRITEABLE, %d\n", (int)wsi);
				n = libwebsocket_write(wsi, &broadcastMsg[LWS_SEND_BUFFER_PRE_PADDING], broadcastLength, LWS_WRITE_TEXT);
				//fprintf(stdout, "CALLBACK_SERVER_WRITEABLE END\n");
				break;

			case LWS_CALLBACK_BROADCAST:
		#ifdef DEBUG_WEBSERVER
				fprintf(stdout, "Mirror LWS_CALLBACK_BROADCAST\n");
		#endif
				//fprintf(stdout, "!!!!!!!!!!!!!!!!!!!!Mirror LWS_CALLBACK_BROADCAST\n");
				n = libwebsocket_write(wsi, &broadcastMsg[LWS_SEND_BUFFER_PRE_PADDING], broadcastLength, LWS_WRITE_TEXT);
		#ifdef DEBUG_WEBSERVER
				fprintf(stdout, "LWS_CALLBACK_BROADCAST END, length: %d\n", broadcastLength);
		#endif
				break;

			case LWS_CALLBACK_RECEIVE:
		#ifdef DEBUG_WEBSERVER
				fprintf(stdout, "Mirror LWS_CALLBACK_RECEIVE, %d\n", (int)wsi);

				fprintf(stderr, "Received command width length: %d\n", len);
		#endif
				memcpy((char*)&broadcastMsg[LWS_SEND_BUFFER_PRE_PADDING], in, len);
				memcpy((char*)dataMsg, (char*)&broadcastMsg[LWS_SEND_BUFFER_PRE_PADDING], len);
				broadcastLength = len;
				dataMsg[len] = 0;
				printf("!!!!HEI: %s\n", dataMsg);
				Data::getInstance()->parseJsonMsg((char*)dataMsg);
				/*
				if (ringbuffer[ringbuffer_head].payload)
					free(ringbuffer[ringbuffer_head].payload);

				ringbuffer[ringbuffer_head].payload =
						malloc(LWS_SEND_BUFFER_PRE_PADDING + len +
								  LWS_SEND_BUFFER_POST_PADDING);
				ringbuffer[ringbuffer_head].len = len;
				memcpy((char *)ringbuffer[ringbuffer_head].payload +
							  LWS_SEND_BUFFER_PRE_PADDING, in, len);
				if (ringbuffer_head == (MAX_MESSAGE_QUEUE - 1))
					ringbuffer_head = 0;
				else
					ringbuffer_head++;

				if (((ringbuffer_head - pss->ringbuffer_tail) %
						  MAX_MESSAGE_QUEUE) > (MAX_MESSAGE_QUEUE - 10))
					libwebsocket_rx_flow_control(wsi, 0);
	*/
				// Received new data from one client. Send request for new callback ("case LWS_CALLBACK_SERVER_WRITEABLE") for all connected clients
				// when it becomes possible to write without blocking
				//libwebsocket_callback_on_writable(context, wsi);
				libwebsocket_callback_on_writable_all_protocol(
							       libwebsockets_get_protocol(wsi));
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
				fprintf(stderr, "!!! callbackDataWebSocket(), default case? Reason %d**********\n", (int)reason);
				break;
			}

			return 0;
}

unsigned char buf[LWS_SEND_BUFFER_PRE_PADDING + 1024 +
							  LWS_SEND_BUFFER_POST_PADDING];

void DataWebSocket::broadcastMsgToClients(char* msg, int nLen) {
	libwebsocket_protocols* protoc = Webserver::getImplementedProtocols();
	buf[LWS_SEND_BUFFER_PRE_PADDING] = 'x';
	memcpy((char*)&broadcastMsg[LWS_SEND_BUFFER_PRE_PADDING], msg, nLen);
	broadcastLength = nLen;
	libwebsockets_broadcast(&protoc[PROTOCOL_LWS_MIRROR], &buf[LWS_SEND_BUFFER_PRE_PADDING], 1); //PROTOCOL_LWS_MIRROR = 2
#ifdef DEBUG_WEBSERVER
	printf("Broadcast %d bytes\n", nLen);
#endif
}
