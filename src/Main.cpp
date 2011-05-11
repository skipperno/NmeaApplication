/*
 * Main.cpp
 *
 *  Created on: 2. mai 2011
 *      Author: nn
 */

#include <iostream>
#include <stdio.h>

#include "services/TcpServer.h"
#include "NmeaHandler.h"


int main(int argc, char **argv)
{
	printf("Hello\n");
	//cout << "Hei 2 !!!" << endl; // prints !!!Hello World!!!

	TcpServer tcpServer;
	tcpServer.serverSocket_start();

	NmeaHandler nmeaHandler;
	nmeaHandler.runHandler(); // !!! Blocking function
}
