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
//#include "../utility/ip.h"

#include <signal.h>
#include "../NmeaHandler.h"
#include "Dispatcher.h"

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

void sigpipe_handler(int nSignal);



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

void SocketClientPipe::catchClosedSocket() {
	signal(SIGPIPE, sigpipe_handler); // catch socket closing
}

int SocketClientPipe::startClientSocket(int conn_s) {
	m_sockd = conn_s;
	int ret;
	ret = pthread_create(&threadClient, NULL, runClientSocket, (void*) this);
	return ret;
}

void * runClientSocket(void *ptr) {
	SocketClientPipe * socketClientPipe = (SocketClientPipe *)ptr;
//void SocketClientPipe::runClientSocket() {
	socketClientPipe->catchClosedSocket(); //TODO: move to server

	socketClientPipe->soketOk = 1;
	printf("Client CONNECTED, id: %d\n", socketClientPipe->m_sockd);

	char recCommand[40];

	while(true) {

		if (socketClientPipe->waitOnCommand(recCommand) == 0) {
			if(recCommand[0] == 'R') {
				NmeaHandler::setRange(recCommand[1] - 0x30);
			} else {
				printf("Received unknown command: %s\n", recCommand);
			}
		} else {
			printf("Disconnect\n");
			Dispatcher::onDisconnected(socketClientPipe);
			return NULL;
		}
	}

	return NULL;
}

int SocketClientPipe::waitOnCommand(char* recCommand) {
	printf("Wait on command\n");
	int nTotLength = Readline(m_sockd, recCommand, 39);
	printf ("ReadLine end\n");

	if (nTotLength <= 0) {
		fprintf(stderr, "***********ERROR, received: %d\n", nTotLength);
		return -1;
	}


	recCommand[nTotLength] = 0;
	printf("rec: %s\n", recCommand);
	return 0;
}

void sigpipe_handler(int nSignal) {
	printf("SIGPIPE caught\n");
	//soketOk = 0;
}

int SocketClientPipe::socketClientPipe_send(const void *vptr, size_t nSize) {
	ssize_t nwritten;
	const void * buffer = vptr;
	//char bb []= {22,33,44,33,44,44,44};

	if (m_sockd <= 0 || soketOk == 0) {
		printf("!!! Cannot write to socket. Closed\n");
		return 0;
	}

	if ((nwritten = write(m_sockd, buffer, nSize)) <= 0) {
		if (errno == EINTR) {
			nwritten = 0;
			printf("nwritten = 0 !!!!\n");
		} else {
			printf("Else !!!!\n");
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

int SocketClientPipe::socketClientPipe_readAllParams(int conn_s) {
	char bufferRec[MAX_REQUEST_LENGTH];
	char recCommand[40];
	char bufferSend[MAX_RESPONSE_LENGTH];

	memset(bufferSend, 0, MAX_RESPONSE_LENGTH);
	memset(bufferRec, 0, MAX_REQUEST_LENGTH);
	fprintf(stderr, "Read msg from client\n");

	if (conn_s < 0) {
		printf("Error socketClientPipe_readAllParams\n");
		return -1;
	}

	int nTotLength = Readline(conn_s, recCommand, 39);
	if (nTotLength <= 0) {
		fprintf(stderr, "***********ERROR, received: %d\n", nTotLength);
		return 0;
	}

	recCommand[nTotLength] = 0;
	printf("rec: %s\n", recCommand);

	int nType = recCommand[2] - 0x30;
	int nChann = recCommand[5] - 0x30;
	int nRange = recCommand[8] - 0x30;

	NmeaHandler::getInstance()->setRange(nRange);
	//printf("Received from client: %d bytes\n", nTotLength);
	//usleep(10000);

	char temp[2000];
	char servText[8000];
	if (!NmeaHandler::getInstance()->getLastEchoMessage(servText))
		printf("Error getting last Echologg message\n");
	//Mock::getString(servText);
	//servText[256] = 0; // null terminate
	sprintf(temp, "%s\r\n", &servText[12]);

	socketClientPipe_write(conn_s, temp, strlen(temp)); //"GGA,10,0,1,1,98.5,3,1\r\n", 23);
	printf("sent data to php\n");
	/*
	 nTotLength = Readline(conn_s, bufferRec, MAX_REQUEST_LENGTH - 1);
	 bufferRec[nTotLength] = 0;
	 //nLength = postHeader_getData(bufferRec, &postHeaderData);
	 */
	return -1;
}

ssize_t SocketClientPipe::socketClientPipe_write(int sockd, const void *vptr,
		size_t nSize) {
	ssize_t nwritten;
	//ssize_t nWrittenTot = 0;
	const void * buffer = vptr;

	if (sockd < 0 || soketOk == 0) {
		printf("!!! Cannot write to socket. Closed\n");
		return 0;
	}

	//while (nSize > 0) {
	if ((nwritten = write(sockd, buffer, nSize)) <= 0) {
		if (errno == EINTR) {
			nwritten = 0;
			printf("nwritten = 0 !!!!\n");
		} else {
			printf("Else !!!!\n");
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

