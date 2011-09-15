/*
 * SocketClientPipe.cpp
 *
 *  Created on: 2. mai 2011
 *      Author: Ernad Secic
 */

#include "SocketClientPipe.h"

#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h> /* close */
#include <string.h>
#include <stdio.h>
#include <stdlib.h> //atoi
//#include "../utility/ip.h"

#include <signal.h>

#include "../MsgInHandler.h"
#include "Dispatcher.h"
#include "../data/Data.h"

#include <exception>
using namespace std;

typedef struct {
	char formID[7];
	char command;
	int canID;
	char loginID[64];
} postHeader;

pthread_mutex_t changingID_mutex;
pthread_mutex_t webClient_mutex;

char dummyBuf[400 * 4];
int dummyBufLength;


void * runClientSocket(void *ptr);

SocketClientPipe::SocketClientPipe() {
	// TODO Auto-generated constructor stub
	m_sockd = -1;
	soketOk = -1;
}

SocketClientPipe::~SocketClientPipe() {
	// TODO Auto-generated destructor stub
	m_sockd = -1;
}



int SocketClientPipe::startClientSocket(int conn_s, int nSocketType) {
	m_sockd = conn_s;
	this->nSocketType = nSocketType;
	int ret;


	ret = pthread_create(&threadClient, NULL, runClientSocket, (void*) this);
	return ret;
}

void * runClientSocket(void *ptr) {
	SocketClientPipe * socketClientPipe = (SocketClientPipe *)ptr;
	printf("starter thread 1\n");

	printf("starter thread 2\n");
	socketClientPipe->soketOk = 1;
	printf("starter thread 3\n");
	printf("Client CONNECTED, id: %d\n", socketClientPipe->m_sockd);

	char dataMsg[1000];
	if(socketClientPipe->nSocketType == SOCK_CONFIG) {
		Data::getInstance()->getJsonTop(dataMsg);
		//Data::getInstance()->getJsonData(dataMsg);
		socketClientPipe->socketClientPipe_send(dataMsg, strlen(dataMsg));
		printf("SENT: %s\n", dataMsg);
		printf("SENT: %d\n", (strlen(dataMsg)));
	}

	while(true) {

		if (socketClientPipe->waitOnCommand(dataMsg, 1000) == 0) {
			Data::getInstance()->parseJsonMsg(dataMsg);
			//Data::getInstance()->getJsonData(dataMsg);
			//socketClientPipe->socketClientPipe_send(dataMsg, strlen(dataMsg));

			/*if(recCommand[0] == 'R') {
				MsgInHandler::setRange(recCommand[1] - 0x30);
			} else if(recCommand[0] == 'G') {
				int nGain = atoi(&recCommand[1]);
				MsgInHandler::setGain(nGain);
			} else {
				printf("Received unknown command: %s\n", recCommand);
			}*/
		} else {
			printf("Disconnect\n");
			Dispatcher::onDisconnected(socketClientPipe);
			return NULL;
		}
	}

	return NULL;
}

int SocketClientPipe::waitOnCommand(char* recCommand, int nLength) {
	printf("Wait on command\n");
	int nTotLength = readAvailable(m_sockd, recCommand, nLength);
	printf ("readAvailable end\n");

	if (nTotLength <= 0) {
		fprintf(stderr, "***********ERROR, received: %d\n", nTotLength);
		return -1;
	}


	recCommand[nTotLength] = 0;
	printf("rec: %s\n", recCommand);
	return 0;
}



int SocketClientPipe::socketClientPipe_send(const void *vptr, size_t nSize) {
	ssize_t nwritten;
	const void * buffer = vptr;
	//char bb []= {22,33,44,33,44,44,44};

	if (m_sockd <= 0 || soketOk == 0) {
		printf("!!! Cannot write to socket. Closed. (socketClientPipe_send)\n");
		return 0;
	}

	if ((nwritten = write(m_sockd, buffer, nSize)) <= 0) {
		if (errno == EINTR) {
			nwritten = 0;
			printf("nwritten = 0 !!!!\n");
		} else {
			printf("Else !!!! socketClientPipe_send\n");
			soketOk = 0;
			close(m_sockd);
			m_sockd = 0;
			return -1;
		}
	} else {
		//printf("Sent: %d of %d\n", nwritten, nSize);
	}

	return nwritten;
}


ssize_t SocketClientPipe::socketClientPipe_write(int sockd, const void *vptr,
		size_t nSize) {
	ssize_t nwritten;
	//ssize_t nWrittenTot = 0;
	const void * buffer = vptr;

	if (sockd < 0 || soketOk == 0) {
		printf("!!! Cannot write to socket. Closed. (socketClientPipe_write)\n");
		return 0;
	}

	//while (nSize > 0) {
	if ((nwritten = write(sockd, buffer, nSize)) <= 0) {
		if (errno == EINTR) {
			nwritten = 0;
			printf("nwritten = 0 !!!!\n");
		} else {
			printf("Else !!!! socketClientPipe_write\n");
			return -1;
		}
	}
	//	write(sockd, "\r\n", 2);
	//printf("written: %d\n", nwritten);
	/*	nWrittenTot += nwritten;
	 nSize -= nwritten;
	 buffer += nwritten;
	 }*/

	return nwritten; //nWrittenTot;
}

/*  Read a line from a socket  */

ssize_t SocketClientPipe::readAvailable(int sockd, char *buffer, size_t maxlen) {
	size_t rc;

	if (sockd < 0)
		return 0;

	if ((rc = read(sockd, buffer, maxlen)) > 0) {
		return rc;
	} else {
		if (errno == EINTR)
			return 0;
		return -1;
	}
}


/*  Read a line from a socket  */

ssize_t SocketClientPipe::Readline(int sockd, char *buffer, size_t maxlen) {
	size_t n, rc;
	char c;

	if (sockd < 0)
		return 0;

	for (n = 0; n < maxlen; n++) {

		if ((rc = read(sockd, &c, 1)) == 1) {
			printf("Rec: %d\n", c);
			if ((c == '\n')) { // && (*(buffer-1) == '\r')) {
				//n--;
				break;
			}
			*buffer++ = c;
		} else if (rc == 0) {
			if (n == 1)
				return 0;
			else
				break;
		} else {
			if (errno == EINTR)
				continue;
			return -1;
		}
	}

	*buffer = 0;
	return n;
}

