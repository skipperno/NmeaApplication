/*
 * ESignal.h
 *
 *  Created on: Aug 26, 2010
 *      Author: root
 */

#ifndef ESIGNAL_H_
#define ESIGNAL_H_


class ESignal {
public:
	ESignal(unsigned int signalType, void* msg);
	virtual ~ESignal();

	unsigned int signalType;
	void* msg;
};

#endif /* ESIGNAL_H_ */
