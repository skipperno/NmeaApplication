/*
 * Simulator.h
 *
 *  Created on: May 27, 2012
 *      Author: ernad
 */

#ifndef SIMULATOR_H_
#define SIMULATOR_H_

class Simulator {
public:
	Simulator();
	virtual ~Simulator();
	static int getNextMessage(char* msg, int length);
private:
	static void openSimulatorFile();
};

#endif /* SIMULATOR_H_ */
