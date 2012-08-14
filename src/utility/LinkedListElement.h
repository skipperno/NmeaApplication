/*
 * LinkedListElement.h
 *
 *  Created on: Aug 24, 2010
 *      Author: root
 */

#ifndef LINKEDLISTELEMENT_H_
#define LINKEDLISTELEMENT_H_

class EByteArray;

class LinkedListElement {
public:
	LinkedListElement(void* listObject);
	virtual ~LinkedListElement();

	void* listObject;
	LinkedListElement* nextListElement;
};

#endif /* LINKEDLISTELEMENT_H_ */
