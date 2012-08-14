/*
 * Backlight.cpp
 *
 *  Created on: Mar 2, 2012
 *      Author: ernad
 */

#include "Backlight.h"

#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <linux/fs.h>
#include <assert.h>

#include <poll.h>

Backlight::Backlight() {
	// TODO Auto-generated constructor stub

}

Backlight::~Backlight() {
	// TODO Auto-generated destructor stub
}


int Backlight::setBacklight(int pwmWidth) {
	int exportfd;
	char pwmString[4];

	exportfd = open("/sys/class/backlight/pwm-backlight.0/brightness", O_WRONLY);
	if (exportfd < 0) {
		printf("Cannot open Backlight to export it %d\n", errno);
		return -1;
	}

	sprintf(pwmString, "%d", pwmWidth);
	write(exportfd, pwmString, strlen(pwmString) + 1); // pwmWidth = 0 => backlight is off, pwmWidth = 100 => backlight is 100%
	close(exportfd);

	return 0;
}
