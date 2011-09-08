/*
 * LinkedList.cpp
 *
 *  Created on: Aug 24, 2010
 *      Author: root
 */

#include "LinkedList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



LinkedList::LinkedList() {
	p_linkedListStartElement = NULL;
	p_linkedListEndElement = NULL;
	nListSize = 0;
}

LinkedList::~LinkedList() {

}

unsigned int LinkedList::size() {
	return nListSize;
}
/////////////////////////////////////////////////////////
//
//
// return: list size (OK) or -1 (ERROR)
/////////////////////////////////////////////////////////
int LinkedList::enque(void* newElement) {
	if (newElement == NULL)
		return -1;
	//printf("list %s: enqueue before: %u\n", debugId, nListSize);

	LinkedListElement* p_linkedListTempEndElement;
	LinkedListElement* p_linkedListNewElement = new LinkedListElement((void*)newElement);

	if (p_linkedListStartElement != NULL) { // list is not empty
		p_linkedListTempEndElement = p_linkedListEndElement;
		p_linkedListEndElement = p_linkedListNewElement;
		p_linkedListTempEndElement->nextListElement = p_linkedListNewElement;
	} else {
		p_linkedListStartElement = p_linkedListNewElement;
		p_linkedListEndElement = p_linkedListStartElement;
	}

	nListSize++;
	//printf("list %s: enqueue after: %u\n", debugId, nListSize);
	return nListSize;
}


void* LinkedList::deque() {
	void* firstElement = NULL;
	LinkedListElement* p_tempElement = NULL;
	//printf("list %s: dequeue før: %u\n", debugId, nListSize);

	if (nListSize > 0) {
		if (p_linkedListStartElement == NULL) {
			printf("Never? LinkedList::deque()\n");
			return NULL;
		}

		firstElement = p_linkedListStartElement->listObject;
		p_tempElement = p_linkedListStartElement->nextListElement;
		delete p_linkedListStartElement;
		p_linkedListStartElement = p_tempElement;
		nListSize --;
	}
	//printf("list %s: dequeue after: %u\n", debugId, nListSize);

	if (nListSize == 0) {
		p_linkedListEndElement = NULL;
		p_linkedListStartElement = NULL;
	}

	return firstElement;
}

void LinkedList::setDebugId(const char* debugId)  {
	strcpy(this->debugId, debugId);
}
