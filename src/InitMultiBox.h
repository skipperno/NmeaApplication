/*
 * InitMultiBox.h
 *
 *  Created on: Mar 9, 2012
 *      Author: ernad
 */

#ifndef INITMULTIBOX_H_
#define INITMULTIBOX_H_

class InitMultiBox {
public:
	InitMultiBox();
	virtual ~InitMultiBox();

	bool searchNewConfiguration();
	bool setDefaultConfiguration();
	bool setConfiguration();
};

#endif /* INITMULTIBOX_H_ */
