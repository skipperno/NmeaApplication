/*
 * LinkedListElement.cpp
 *
 *  Created on: Aug 24, 2010
 *      Author: root
 */

#include "LinkedListElement.h"
#include <stdlib.h>

LinkedListElement::LinkedListElement(void* listObject) {
	this->listObject = listObject;
	nextListElement = NULL;
}

LinkedListElement::~LinkedListElement() {
	// TODO Auto-generated destructor stub
}
