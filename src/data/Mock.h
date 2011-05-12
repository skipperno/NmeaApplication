/*
 * Mock.h
 *
 *  Created on: 3. mai 2011
 *      Author: Ernad Secic
 */

#ifndef MOCK_H_
#define MOCK_H_

class Mock {
public:
	Mock();
	virtual ~Mock();

	static int getNumber();
	static void getString(char * chBuff);
	static void getByteString(char * chBuff);

private:

};

#endif /* MOCK_H_ */
