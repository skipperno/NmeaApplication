/*
 * Backlight.h
 *
 *  Created on: Mar 2, 2012
 *      Author: ernad
 */

#ifndef BACKLIGHT_H_
#define BACKLIGHT_H_

class Backlight {
public:
	Backlight();
	virtual ~Backlight();
	static int setBacklight(int pwmWidth);
};

#endif /* BACKLIGHT_H_ */
