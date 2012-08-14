/*
 * EByteArray.h
 *
 *  Created on: Aug 24, 2010
 *      Author: root
 */

#ifndef EBYTEARRAY_H_
#define EBYTEARRAY_H_

class EByteArray {
public:
	EByteArray();
	virtual ~EByteArray();

	char* data();

	void resize(unsigned int newSize);
	void append(const char* dataToAppend);
	void append(const char* dataToAppend, unsigned int nLength);
	void append(char charToAppend);
	void append(EByteArray& arrayToAppend);
	unsigned int length();
	void setDataLength(unsigned int newLength);
	void clear();
	void clearLength(); // if you want to reuse allocated memory

	void setMsgType(unsigned short msgType);
	unsigned short getMsgType();

private:
	char* m_data;
	unsigned int m_length;
	unsigned int reservedLength;
	unsigned short m_msgType;
};

#endif /* EBYTEARRAY_H_ */
