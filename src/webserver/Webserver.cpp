/*
 * Server.cpp
 *
 *  Created on: Sep 22, 2011
 *      Author: ernad
 */

#define LWS_NO_FORK


#include "Webserver.h"

#include "ServerConstants.h"

//#define DEBUG_WEBSERVER

#define LOCAL_RESOURCE_PATH DATADIR"/libwebsockets-test-server"
#define SERVER_PATH "/www" // /test/files"


Webserver::Webserver() {
	// TODO Auto-generated constructor stub

}

Webserver::~Webserver() {
	// TODO Auto-generated destructor stub
}
/*
 * libwebsockets-test-server - libwebsockets test implementation
 *
 * Copyright (C) 2010-2011 Andy Green <andy@warmcat.com>
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation:
 *  version 2.1 of the License.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *  MA  02110-1301  USA
 */


/////////////////////////////////////////////////////////////////



/* list of supported protocols and callbacks */

static struct libwebsocket_protocols protocols[] = {
	// first protocol must always be HTTP handler
	{
		"http-only",		// name
		Webserver::callback_http,		// callback
		0					// per_session_data_size
	},
	{
		"dumb-increment-protocol",
		EchoDataWebSocket::callback_dumb_increment,
		sizeof(struct sessionDataProtocol_1),
	},
	{
		"lws-mirror-protocol",
		DataWebSocket::callbackDataWebSocket, //callback_lws_mirror,
		sizeof(struct sessionDataProtocol_2)
	},
	{
		NULL, NULL, 0		// End of list
	}
};

libwebsocket_protocols* Webserver::getImplementedProtocols() {
	return protocols;
}


struct a_message {
	void *payload;
	size_t len;
};
/*
#define MAX_MESSAGE_QUEUE 64
static struct a_message ringbuffer[MAX_MESSAGE_QUEUE];
static int ringbuffer_head;
*/

int Webserver::callback_http(struct libwebsocket_context * context,
		struct libwebsocket *wsi,
		enum libwebsocket_callback_reasons reason, void *user,
							   void *in, size_t len)
{
	char client_name[256];
	char client_ip[256];
	char wantedFile[256];
	char extension[64];
#ifdef DEBUG_WEBSERVER
	fprintf(stderr, "callback HTTP, fd: %d, reason: %s\n", libwebsocket_get_socket_fd(wsi), ServerConstants::getCallbackReasonText(reason));
#endif

	switch (reason) {
	case LWS_CALLBACK_HTTP:
#ifdef DEBUG_WEBSERVER
		fprintf(stdout, "serving HTTP URI %s\n", (char *)in);
#endif

		if (in && strcmp((char*)in, "/") == 0) {
			sprintf(wantedFile, "%s%s", SERVER_PATH, "/test.html");

			if (libwebsockets_serve_http_file(wsi, wantedFile, "text/html"))
				fprintf(stderr, "Failed to send HTTP file, TODO: ernad release\n");
			break;
		}

		// fine file extension and mime type
		if(MimeTypes::getMimeType((const char *)in, extension)) {
			sprintf(wantedFile, "%s%s", SERVER_PATH, (char*)in);
			if (libwebsockets_serve_http_file(wsi,wantedFile, extension)) { //"image/x-icon"))
				fprintf(stderr, "Failed to send file: %s\n", wantedFile);
			} else {
#ifdef DEBUG_WEBSERVER
				fprintf(stderr, "=====Sent file: %s\n", wantedFile);
#endif
			}
			break;
		} else {
			fprintf(stderr, "Failed to fine extension: %s\n", wantedFile);
		}

		break;



	/*
	 * callback for confirming to continue with client IP appear in
	 * protocol 0 callback since no websocket protocol has been agreed
	 * yet.  You can just ignore this if you won't filter on client IP
	 * since the default uhandled callback return is 0 meaning let the
	 * connection continue.
	 */

	case LWS_CALLBACK_FILTER_NETWORK_CONNECTION:

		libwebsockets_get_peer_addresses((int)(long)user, client_name,
			     sizeof(client_name), client_ip, sizeof(client_ip));
#ifdef DEBUG_WEBSERVER
		fprintf(stderr, "Received network connect from %s (%s)\n",
							client_name, client_ip);
#endif

		/* if we returned non-zero from here, we kill the connection */
		break;

	default:
#ifdef DEBUG_WEBSERVER
		fprintf(stderr, "callback_http(), default case? Reason %d**********\n", (int)reason);
#endif
		break;
	}

	return 0;
}


/*
 * this is just an example of parsing handshake headers, you don't need this
 * in your code unless you will filter allowing connections by the header
 * content
 */

static void
dump_handshake_info(struct lws_tokens *lwst)
{
	int n;
	static const char *token_names[] = {
		/*[WSI_TOKEN_GET_URI]		=*/ "GET URI",
		/*[WSI_TOKEN_HOST]		=*/ "Host",
		/*[WSI_TOKEN_CONNECTION]	=*/ "Connection",
		/*[WSI_TOKEN_KEY1]		=*/ "key 1",
		/*[WSI_TOKEN_KEY2]		=*/ "key 2",
		/*[WSI_TOKEN_PROTOCOL]		=*/ "Protocol",
		/*[WSI_TOKEN_UPGRADE]		=*/ "Upgrade",
		/*[WSI_TOKEN_ORIGIN]		=*/ "Origin",
		/*[WSI_TOKEN_DRAFT]		=*/ "Draft",
		/*[WSI_TOKEN_CHALLENGE]		=*/ "Challenge",

		/* new for 04 */
		/*[WSI_TOKEN_KEY]		=*/ "Key",
		/*[WSI_TOKEN_VERSION]		=*/ "Version",
		/*[WSI_TOKEN_SWORIGIN]		=*/ "Sworigin",

		/* new for 05 */
		/*[WSI_TOKEN_EXTENSIONS]	=*/ "Extensions",

		/* client receives these */
		/*[WSI_TOKEN_ACCEPT]		=*/ "Accept",
		/*[WSI_TOKEN_NONCE]		=*/ "Nonce",
		/*[WSI_TOKEN_HTTP]		=*/ "Http",
	};

	for (n = 0; n < WSI_TOKEN_COUNT; n++) {
		if (lwst[n].token == NULL)
			continue;

		fprintf(stdout, "TOKEN    %s = %s\n", token_names[n], lwst[n].token);
	}
}


int Webserver::mainLoop()
{
	const char *cert_path ="files/libwebsockets-test-server.pem";

	const char *key_path ="files/libwebsockets-test-server.key.pem";
	int port = 7681;
	int use_ssl = 0;
	struct libwebsocket_context *context;
	int opts = 0;

	const char * interface = NULL;


	fprintf(stderr, "libwebsockets test server\n"
			"(C) Copyright 2010-2011 Andy Green <andy@warmcat.com> "
						    "licensed under LGPL2.1\n");

	if (!use_ssl)
		cert_path = key_path = NULL;

	context = libwebsocket_create_context(port, interface, protocols,
				libwebsocket_internal_extensions,
				cert_path, key_path, -1, -1, opts);
	if (context == NULL) {
		fprintf(stderr, "libwebsocket init failed\n");
		return -1;
	}


#ifdef LWS_NO_FORK

	/*
	 * This example shows how to work with no forked service loop
	 */

	fprintf(stderr, " Using no-fork service loop\n");

	while (1) {
		/*
		 * This example server does not fork or create a thread for
		 * websocket service, it all runs in this single loop.  So,
		 * we have to give the websockets an opportunity to service
		 * "manually".
		 *
		 * If no socket is needing service, the call below returns
		 * immediately and quickly.
		 */

		libwebsocket_service(context, 50);
	}

#else

	/*
	 * This example shows how to work with the forked websocket service loop
	 */

	fprintf(stderr, " Using forked service loop\n");

	/*
	 * This forks the websocket service action into a subprocess so we
	 * don't have to take care about it.
	 */

	n = libwebsockets_fork_service_loop(context);// libwebsockets_fork_service_loop(context);

	if (n < 0) {
		fprintf(stderr, "Unable to fork service loop %d\n", n);
		return 1;
	}
/*
	while (1) {
		//n = libwebsocket_service(context,100);
		usleep(500000);


	//	libwebsockets_broadcast(&protocols[PROTOCOL_DUMB_INCREMENT],
		//			&buf[LWS_SEND_BUFFER_PRE_PADDING], 1);
	}*/

#endif

//	libwebsocket_context_destroy(context);

	return 0;
}
