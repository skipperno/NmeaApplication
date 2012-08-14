/*
 * ESignal.cpp
 *
 *  Created on: Aug 26, 2010
 *      Author: root
 */

#include "ESignal.h"
#include "libio.h" // NULL

ESignal::ESignal(unsigned int signalType, void* msg) {
	this->signalType = signalType;
	this->msg = msg;
}

ESignal::~ESignal() {

}
