/*
 * TcpServer.cpp
 *
 *  Created on: 2. mai 2011
 *      Author: Ernad Secic
 */

#include "TcpServer.h"
#include "SocketClientPipe.h"
#include "Dispatcher.h"

#include <pthread.h>

void * runServerThread(void *ptr);
pthread_t thread1;

TcpServer::TcpServer() {
	// TODO Auto-generated constructor stub

}

TcpServer::~TcpServer() {
	// TODO Auto-generated destructor stub
}

int TcpServer::serverSocket_start(int nServerPort) {
	this->nServerPort = nServerPort;
	int ret;
	ret = pthread_create(&thread1, NULL, runServerThread, (void*) this);
	return ret;
}

void * runServerThread(void *ptr) {
	int list_s; /*  listening socket          */
	TcpServer* server = (TcpServer*)ptr;

		struct sockaddr_in servaddr; /*  socket address structure  */

		unsigned int addrlen;

		if ((list_s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
			fprintf(stderr, "TCP_SERVER: Error creating listening socket.\n");
			return NULL;
		}

		fprintf(stderr, "start TCP_SERVER, port %d\n", server->nServerPort);

		memset(&servaddr, 0, sizeof(servaddr));
		servaddr.sin_family = AF_INET;
		servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
		servaddr.sin_port = htons(server->nServerPort);

		if (bind(list_s, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) {
			fprintf(stderr, "TCP_SERVER: Error calling bind()\n");
			return NULL;
		}
		fprintf(stderr, "TCP_SERVER: bind successed\n");

		if (listen(list_s, 1) < 0) {
		//if (listen(list_s, LISTENQ) < 0) {
			fprintf(stderr, "TCP_SERVER: Error calling listen()\n");
			return NULL;
		}
		fprintf(stderr, "TCP_SERVER: Listen successed\n");

		while (1) {
			int conn_s; /*  connection socket         */
			/*  Wait for a connection, then accept() it  */
			addrlen = sizeof(servaddr);
			if ((conn_s = accept(list_s, (struct sockaddr *) &servaddr, &addrlen))
					< 0) {
				fprintf(stderr, "TCP_SERVER: Error calling accept()\n");
				return NULL;
			}
			fprintf(stderr, "TCP_SERVER, Client accepted\n");

			SocketClientPipe* socketClient = new SocketClientPipe();
if(server->nServerPort == 2005)
			socketClient->startClientSocket(conn_s, SOCK_DATA);
else
	socketClient->startClientSocket(conn_s, SOCK_ECHO);
			Dispatcher::addClient(socketClient);

		//	socketClientPipe_handleRequest(conn_s);
		}

		return 0;
}
