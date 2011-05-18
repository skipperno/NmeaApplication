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
#include <pthread.h> // mutex

#include "../NmeaHandler.h"

typedef struct {
	char formID[7];
	char command;
	int canID;
	char loginID[64];
} postHeader;

SocketClientPipe::SocketClientPipe() {
	// TODO Auto-generated constructor stub

}

SocketClientPipe::~SocketClientPipe() {
	// TODO Auto-generated destructor stub
}


pthread_mutex_t changingID_mutex;

pthread_mutex_t webClient_mutex;


void sigpipe_handler();
char soketOk = 1;
/*
void socketClientPipe_setMutex() {
	pthread_mutex_lock(&changingID_mutex);
}

void socketClientPipe_clearMutex() {
	pthread_mutex_unlock(&changingID_mutex);
}
int socketClientPipe_readAllParams(int conn_s);
*/
void SocketClientPipe::socketClientPipe_handleRequest(int conn_s) {
	soketOk = 1;
	//signal(SIGPIPE, sigpipe_handler); // catch socket closing (Ernad)

	socketClientPipe_readAllParams(conn_s);

#ifdef DEBUG_CLIENT
	printf("Closing connection to client\n");
#endif
	//printf("Closed connection to client\n");
	if (close(conn_s) < 0) {
		fprintf(stderr, "TCP_SERVER: Error calling close()\n");
	}
}

void sigpipe_handler()
{
    printf("SIGPIPE caught\n");
    soketOk=0;
}

int  SocketClientPipe::socketClientPipe_readAllParams(int conn_s) {
	char bufferRec[MAX_REQUEST_LENGTH];
	char bufferRemoteIP[40];
	char bufferSend[MAX_RESPONSE_LENGTH];

	memset(bufferSend, 0, MAX_RESPONSE_LENGTH);
	memset(bufferRec, 0, MAX_REQUEST_LENGTH);
	//printf("Read msg from client\n");

	if (conn_s < 0) {
		printf("Error socketClientPipe_readAllParams\n");
		return -1;
	}

	int nTotLength = Readline(conn_s, bufferRemoteIP, 39);
	if (nTotLength <= 0) {
		printf("***********ERROR, received: %d\n", nTotLength);
		return 0;
	}

	bufferRemoteIP[nTotLength] = 0;

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
/*
	nTotLength = Readline(conn_s, bufferRec, MAX_REQUEST_LENGTH - 1);
	bufferRec[nTotLength] = 0;
	//nLength = postHeader_getData(bufferRec, &postHeaderData);
	*/
	return -1;
}



ssize_t SocketClientPipe::socketClientPipe_write(int sockd, const void *vptr, size_t nSize) {
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
			//printf("Rec: %d\n", c);
			if ((c == '\n') ){ // && (*(buffer-1) == '\r')) {
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


