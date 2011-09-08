/*
 * LinkedList.h
 *
 *  Created on: Aug 24, 2010
 *      Author: root
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_


#include "LinkedListElement.h"

class ESignal;


class LinkedList {
public:
	LinkedList();
	virtual ~LinkedList();

	int enque(void* newElement);
	void* deque();
	unsigned int size();

	void setDebugId(const char* debugId);

private:
	int nListSize;
	LinkedListElement* p_linkedListStartElement;
	LinkedListElement* p_linkedListEndElement;
	char debugId[20];
};

#endif /* LINKEDLIST_H_ */
