/*
 * Main.cpp
 *
 *  Created on: 2. mai 2011
 *      Author: Ernad Secic
 */

#include <iostream>
#include <stdio.h>

#include "comm/TcpServer.h"
#include "NmeaHandler.h"


int main(int argc, char **argv)
{
	//TEST TEST
	printf("Hello\n");
	//cout << "Hei 2 !!!" << endl; // prints !!!Hello World!!!

	TcpServer tcpServer;
	tcpServer.serverSocket_start();

	NmeaHandler nmeaHandler;
	nmeaHandler.runHandler(); // !!! Blocking function
}
