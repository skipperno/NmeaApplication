/*
 * EByteArray.cpp
 *
 *  Created on: Aug 24, 2010
 *      Author: root
 */

#include "EByteArray.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

EByteArray::EByteArray() {
	m_length = 0;
	reservedLength = 0;
	m_data = NULL;
	resize(12);
}

EByteArray::~EByteArray() {
	// TODO Auto-generated destructor stub
	if (reservedLength > 0 && m_data != NULL) {
		free(m_data);
		reservedLength = 0;
		m_data = NULL;
	}
}

char* EByteArray::data() {
	return m_data;
}

unsigned int EByteArray::length() {
	return m_length;
}

//////////////////////////////////////////////////
// !!! If copy data to char* "data()", length is not
// updated. This is only case when this function has
// to be used.
//////////////////////////////////////////////////
void EByteArray::setDataLength(unsigned int newLength) {
	if (newLength > reservedLength) {
		resize(newLength);
	}
	m_length = newLength;
}

void EByteArray::resize(unsigned int newSize) {

	if (reservedLength < (newSize + 1)) {
		reservedLength =  newSize + 1;

		char* newData = (char*) malloc(reservedLength);
		memset(newData, 0, reservedLength);
		//newData[reservedLength -1] = 0;

		if (m_data != NULL) {
			memcpy(newData, m_data, m_length);
			free(m_data);
			m_data = NULL;
		}

		m_data = newData;
	}
}

void EByteArray::append(const char* dataToAppend) {
	unsigned int additLength = strlen(dataToAppend);
	append(dataToAppend, additLength);
}

void EByteArray::append(const char* dataToAppend, unsigned int additLength) {
	if (reservedLength < (m_length + additLength) + 1) {
		resize(m_length + additLength); // + 1
	}

	memcpy(&m_data[m_length], dataToAppend, additLength);
	m_length = m_length + additLength;
	//m_data[m_length] = 0; // null terminate if it needs
}

void EByteArray::append(char charToAppend) {
	append(&charToAppend, 1);
}

void EByteArray::append(EByteArray& arrayToAppend) {
	// TODO: error if array is appending to your self.
	/*if (m_data == arrayToAppend.data()) {

	}*/
	append(arrayToAppend.data(), arrayToAppend.length());
}

void EByteArray::clear() {
	if (m_data != NULL)
		free(m_data);
	m_data = NULL;
	m_length = 0;
	reservedLength = 0;
	resize(12);
}

// if you want to reuse allocated memory
void EByteArray::clearLength() {
	m_length = 0;
}

void EByteArray::setMsgType(unsigned short msgType) {
	m_msgType = msgType;
}

unsigned short EByteArray::getMsgType() {
	return m_msgType;
}
