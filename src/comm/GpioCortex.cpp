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

#include <poll.h>

#include "../data/GpioInputEvent.h"

GpioCortex::GpioCortex() {

}

GpioCortex::GpioCortex(const char* ioPinName) {
	// TODO Auto-generated constructor stub
	strcpy(ioPin, ioPinName);
}

GpioCortex::GpioCortex(unsigned char* gpioPins, int nCount) {
	memcpy(ioPinsArray, gpioPins, nCount);
	nPinCount = nCount;
}

GpioCortex::~GpioCortex() {
	// TODO Auto-generated destructor stub
}

int GpioCortex::configureGpioAsOutput(const char* ioPinName) {
	int exportfd;

	strcpy(ioPin, ioPinName);
	// add file for GPIO 116
	exportfd = open("/sys/class/gpio/export", O_WRONLY);
	if (exportfd < 0) {
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
	if (directionfd < 0) {
		printf("Cannot open GPIO direction for %s\n", directionPath);
		return -1;
	}

	write(directionfd, "out", 4);
	close(directionfd);

	return 0;
}

int GpioCortex::configureGpioAsInput(unsigned char ioPinName) {
	int exportfd;
	char pinNameAsText[5];

	sprintf(pinNameAsText, "%u", (unsigned int) ioPinName);

	// add file for GPIO 116
	exportfd = open("/sys/class/gpio/export", O_WRONLY);
	if (exportfd < 0) {
		printf("Cannot open GPIO to export it %d\n", errno);
		return -1;
	}

	write(exportfd, pinNameAsText, strlen(pinNameAsText) + 1); //"116", 4);
	close(exportfd);

	// set direction
	int directionfd;
	char directionPath[100];
	sprintf(directionPath, "/sys/class/gpio/gpio%s/direction", pinNameAsText);
	directionfd = open(directionPath, O_RDWR);//"/sys/class/gpio/gpio149/direction", O_RDWR);
	if (directionfd < 0) {
		printf("Cannot open GPIO direction for %s\n", directionPath);
		return -1;
	}

	write(directionfd, "in", 3);
	close(directionfd);

	return 0;
}

int GpioCortex::setOutputHigh(bool bHigh) {
	// Set value
	int valuefd;
	char outputPath[100];
	sprintf(outputPath, "/sys/class/gpio/gpio%s/value", ioPin);
	valuefd = open(outputPath, O_RDWR); //"/sys/class/gpio/gpio116/value", O_RDWR);
	if (valuefd < 0) {
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

int GpioCortex::setRisingEdge(unsigned char ioPinName, bool bRising) {
	char pinNameAsText[5];
	sprintf(pinNameAsText, "%u", (unsigned int) ioPinName);

	int fd;
	char edgePath[100];

	sprintf(edgePath, "/sys/class/gpio/gpio%s/edge", pinNameAsText);

	fd = open(edgePath, O_WRONLY);
	if (fd < 0) {
		printf("Cannot set GPIO edge for %s\n", edgePath);
		return fd;
	}

	if (bRising)
		write(fd, "rising", 7);
	else
		write(fd, "falling", 8);

	close(fd);
	return 0;
}

int GpioCortex::waitOnEdgeEvent(GpioInputEvent* gpioInputEvent) {
	char pinNameAsText[5];
	struct pollfd fdset[nPinCount];
	int fdCount = nPinCount;
	char valuePath[100];
	int nTimeout = 5000; //[ms]
	char buff[100];

	int fd[nPinCount];
	int ret, len;
	int i;

	for (i = 0; i < nPinCount; i++) {
		configureGpioAsInput(ioPinsArray[i]);
		setRisingEdge(ioPinsArray[i], true);

		sprintf(pinNameAsText, "%u", (unsigned int) ioPinsArray[i]);

		sprintf(valuePath, "/sys/class/gpio/gpio%s/value", pinNameAsText);
		fd[i] = open(valuePath, O_RDONLY | O_NONBLOCK);

		if (fd[i] < 0) {
			printf("Cannot open GPIO value for %s\n", valuePath);
			return -1;
		}

		fdset[i].fd = fd[i];
		fdset[i].events = POLLPRI;
	}

	printf("start new waiting\n");

	while (true) {
	/*	memset((void*) fdset, 0, sizeof(fdset));
		for (i = 0; i < nPinCount; i++) {
			fdset[i].fd = fd;
			fdset[i].events = POLLPRI;
		}*/
		/* fdset[0].fd = STDIN_FILENO;
		 fdset[0].events = POLLIN;

		 fdset[1].fd = fd;
		 fdset[1].events = POLLPRI;*/

		ret = poll(fdset, fdCount, nTimeout);

		if (ret < 0) {
			printf("poll() failed!\n");
			return -1;
		}

		if (ret == 0) {
			//printf("aa\n");
		} else {

			for (i = 0; i < nPinCount; i++) {
				if (fdset[i].revents & POLLPRI) {
					len = read(fdset[i].fd, buff, 100);
					gpioInputEvent->callbackGpioEvent(i);
					//printf("waitOnEdgeEvent() interrupt on GPIO %u, answer: %s\n",
						//	(unsigned int) ioPinsArray[i], buff);
				}
			}
		}
		/*	if (fdset[1].revents & POLLPRI) {
		 len = read(fdset[1].fd, buff, 100);

		 printf("waitOnEdgeEvent() interrupt on GPIO %s, answer: %s\n",
		 ioPin, buff);
		 }

		 if (fdset[0].revents & POLLIN) {
		 (void) read(fdset[0].fd, buff, 1);
		 printf("waitOnEdgeEvent() stdin read 0x%2.2X\n",
		 (unsigned int) buff[0]);
		 }*/
	}
	printf("out of waiting\n");
}

