/*
 * TcpServer.h
 *
 *  Created on: 2. mai 2011
 *      Author: Ernad Secic
 */

#ifndef TCPSERVER_H_
#define TCPSERVER_H_

#include <sys/socket.h>       /*  socket definitions        */
#include <sys/types.h>        /*  socket types              */
#include <arpa/inet.h>        /*  inet (3) funtions         */
#include <unistd.h>           /*  misc. UNIX functions      */

//#include "helper.h"           /*  our own helper functions  */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include "socketClientPipe.h"

#define MAX_LINE_LENGTH           	(1000)
#define SERVER_PORT   				 2004

class TcpServer {
public:
	TcpServer();
	virtual ~TcpServer();

	int serverSocket_start(void);

	int readParams(int conn_s);
	int getNextParam(char* buffer, char* paramName, char* paramValue);
	int readAllParams(int conn_s);

};

#endif /* TCPSERVER_H_ */
