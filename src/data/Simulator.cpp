/*
 * Simulator.cpp
 *
 *  Created on: May 27, 2012
 *      Author: ernad
 */

#include "Simulator.h"

#include <sys/stat.h>
#include <errno.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


FILE * pSimulatorFile = NULL;

char tempSimBuff[512];

Simulator::Simulator() {
	// TODO Auto-generated constructor stub

}

Simulator::~Simulator() {
	// TODO Auto-generated destructor stub
}

int Simulator::getNextMessage(char* msg, int length) {
	int nReadCount = 0;
	if (pSimulatorFile == NULL)
		openSimulatorFile();

	if (pSimulatorFile == NULL) {
		length = 0;
		return 0;
	}

	//&msg[1]
	nReadCount = fread(tempSimBuff, 1, (size_t)512, pSimulatorFile);


	if (nReadCount < 512)  { // END of file? Close and open again
		fclose(pSimulatorFile);
		pSimulatorFile = NULL;
		length = 0;
		openSimulatorFile();
		return 0;
	}

	for (int i = 0; i < 512; i++) {
		msg[i+1] = tempSimBuff[512- i - 1];
	}
	msg[0] = '$';
	msg[513] = '*';
	return 514;
}

void Simulator::openSimulatorFile() {
	pSimulatorFile = fopen("/opt/curtis.bin", "r");
}
