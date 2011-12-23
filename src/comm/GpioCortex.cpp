/*
 * GpioCortex.cpp
 *
 *  Created on: Oct 25, 2011
 *      Author: ernad
 */

#include "GpioCortex.h"

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


GpioCortex::GpioCortex() {
	// TODO Auto-generated constructor stub

}

GpioCortex::~GpioCortex() {
	// TODO Auto-generated destructor stub
}

int GpioCortex::configureGpioAsOutput(const char* ioPinName) {
	int exportfd;

	strcpy(ioPin, ioPinName);
	// add file for GPIO 116
	exportfd = open("/sys/class/gpio/export", O_WRONLY);
	if (exportfd < 0)
	{
	printf("Cannot open GPIO to export it %d\n", errno);
	return -1;
	}

    write(exportfd, ioPin, strlen(ioPin) + 1); //"116", 4);
    close(exportfd);

    // set direction
    int directionfd;
    char directionPath[100];
    sprintf(directionPath, "/sys/class/gpio/gpio%s/direction", ioPin);
    directionfd = open(directionPath, O_RDWR);//"/sys/class/gpio/gpio149/direction", O_RDWR);
    if (directionfd < 0)
    {
    printf("Cannot open GPIO direction for %s\n", directionPath);
    return -1;
    }

    write(directionfd, "out", 4);
    close(directionfd);

    return 0;
}

int GpioCortex::setOutputHigh(bool bHigh) {
	// Set value
	    int valuefd;
	    char outputPath[100];
	    sprintf(outputPath, "/sys/class/gpio/gpio%s/value", ioPin);
	    valuefd = open(outputPath, O_RDWR); //"/sys/class/gpio/gpio116/value", O_RDWR);
	    if (valuefd < 0)
	    {
	    printf("Cannot open GPIO value for %s\n", outputPath);
	    return -1;
	    }
	    if (bHigh)
	    	write(valuefd, "1", 2); //"1"- high, "0" - low
	    else
	    	write(valuefd, "0", 2); //"1"- high, "0" - low

	    close(valuefd);

	    return 0;
}
