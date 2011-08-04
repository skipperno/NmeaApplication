/*
 * SocketClientPipe.h
 *
 *  Created on: 2. mai 2011
 *      Author: Ernad Secic
 */

#ifndef SOCKETCLIENTPIPE_H_
#define SOCKETCLIENTPIPE_H_

#include <sys/types.h>
#include <pthread.h>

#define MAX_REQUEST_LENGTH	2000
#define MAX_RESPONSE_LENGTH	30000

enum socktType{
	SOCK_ECHO,
	SOCK_CONFIG
};

class SocketClientPipe {
public:
	SocketClientPipe();
	virtual ~SocketClientPipe();
	//void catchClosedSocket();
int socketClientPipe_send(const void *vptr, size_t nSize);

ssize_t readAvailable(int sockd, char *buffer, size_t maxlen);
ssize_t Readline(int sockd, char *buffer, size_t maxlen);
void socketClientPipe_setMutex();
void socketClientPipe_clearMutex();

ssize_t socketClientPipe_write(int sockd, const void *vptr, size_t nSize);

int startClientSocket(int conn_s, int nSocketType);
//void runClientSocket(void);

int waitOnCommand(char* recCommand, int nLength);

int soketOk;
int m_sockd;
int nSocketType;
pthread_t threadClient;



};

#endif /* SOCKETCLIENTPIPE_H_ */
