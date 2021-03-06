/*
 * ServerConstants.cpp
 *
 *  Created on: Oct 4, 2011
 *      Author: ernad
 */

#include "ServerConstants.h"

ServerConstants::ServerConstants() {
	// TODO Auto-generated constructor stub

}

ServerConstants::~ServerConstants() {
	// TODO Auto-generated destructor stub
}

const char* callbackReason[] = {"LWS_CALLBACK_ESTABLISHED",
		"LWS_CALLBACK_CLIENT_ESTABLISHED",
		"LWS_CALLBACK_CLOSED",
		"LWS_CALLBACK_RECEIVE",
		"LWS_CALLBACK_CLIENT_RECEIVE",
		"LWS_CALLBACK_CLIENT_RECEIVE_PONG",
		"LWS_CALLBACK_CLIENT_WRITEABLE",
		"LWS_CALLBACK_SERVER_WRITEABLE",
		"LWS_CALLBACK_HTTP",
		"LWS_CALLBACK_BROADCAST",
		"LWS_CALLBACK_FILTER_NETWORK_CONNECTION",//10

		"LWS_CALLBACK_FILTER_PROTOCOL_CONNECTION",
		"LWS_CALLBACK_OPENSSL_LOAD_EXTRA_CLIENT_VERIFY_CERTS",
		"LWS_CALLBACK_OPENSSL_LOAD_EXTRA_SERVER_VERIFY_CERTS",
		"LWS_CALLBACK_OPENSSL_PERFORM_CLIENT_CERT_VERIFICATION",
		"LWS_CALLBACK_CLIENT_APPEND_HANDSHAKE_HEADER",
		"LWS_CALLBACK_CONFIRM_EXTENSION_OKAY",
		"LWS_CALLBACK_CLIENT_CONFIRM_EXTENSION_SUPPORTED",
		/* external poll() management support */
		"LWS_CALLBACK_ADD_POLL_FD",
		"LWS_CALLBACK_DEL_POLL_FD",
		"LWS_CALLBACK_SET_MODE_POLL_FD",//20

		"LWS_CALLBACK_CLEAR_MODE_POLL_FD"
};

const char* ServerConstants::getCallbackReasonText(int nReason) {
	return callbackReason[nReason];
}
