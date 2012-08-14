/*
 * AD7997.cpp
 *
 *  Created on: Oct 21, 2011
 *      Author: ernad
 */

#include "AD7997.h"
//#include <glib.h>
//#include <glib/gprintf.h>

//#include <linux/i2c-dev.h>
#include "i2c-dev.h"

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
#include "../data/Data.h"


//const char* START_CONVERSION_GPIO = "116"; //PXA310
const char* START_CONVERSION_GPIO = "114"; //PXA320
/*
#include <sys/mman.h>
#define GPIO_BASE 0x80840000
volatile unsigned int *PEDR;
volatile unsigned int *PEDDR;
*/

void * runMeasuringThread(void *ptr);

AD7997::AD7997() {
	gpioCortex.configureGpioAsOutput(START_CONVERSION_GPIO);//START_CONVERSION_GPIO);
}

AD7997::~AD7997() {

}



void * runMeasuringThread(void *ptr) {
	AD7997* ad7997 = (AD7997*)ptr;
	ad7997->runThreadImplementation();
	return NULL;
}

void AD7997::runThreadImplementation(void){
	int i2cFd;
	int nTempCounter = 0;

	    char filename[40];
	    int addr = 0x20; //0b00101001;        // The I2C address of the ADC

	    sprintf(filename,"/dev/i2c-0");
	    if ((i2cFd = open(filename,O_RDWR)) < 0) {
	        printf("Failed to open the bus.");
	        /* ERROR HANDLING; you can check errno to see what went wrong */
	        exit(1);
	    }


	    if (ioctl(i2cFd,I2C_SLAVE,addr) < 0) {
	        printf("Failed to acquire bus access and/or talk to slave.\n");
	        /* ERROR HANDLING; you can check errno to see what went wrong */
	        exit(1);
	    }

	    configureConversionAllCh(i2cFd);

	char buf[10] = {0};
		    int data;
		    char channel;
		    char alarm;
		    //unsigned char test;

		    i2c_write_1b(i2cFd, 0);

		    while(1) {
		    	if(nTempCounter%8 == 0)
		    		sleep(1);
		    		//usleep(300);
		    	nTempCounter++;

		    	gpioCortex.setOutputHigh(true);
		    	usleep(2);
		    	gpioCortex.setOutputHigh(false);
		    	usleep(3);

		        if (read(i2cFd,buf,2) != 2) {
		            //printf("Failed to read from the i2c bus:\n");
		            //printf(strerror(errno));
		            //printf("\n\n");
		        } else {
		            data = (((buf[0] & 0b00001111)<<8)+buf[1]) >> 2;

		            alarm = ((buf[0] & 0b10000000)>>7);
		            channel = 1 + ((buf[0] & 0b01110000)>>4);
		           // printf("Channel %02d, Alarm: %d, Data:  %d\n",channel, (int)alarm, data);
		            Data::getInstance()->setPowerMeasurment(channel, data);

		        }
		    }
}

void AD7997::startMeasuringAD7997(void) {
	pthread_create(&threadMeasur, NULL, runMeasuringThread, (void*) this);
}

void AD7997::configureConversionAllCh(int file) {
	unsigned char buf[] = {0x02,0x0f,0xf8};
	i2c_write_3b(file,buf);
}

int AD7997::i2c_write_1b(int fd, unsigned char buf)
{
	int r;
	// we must simulate a plain I2C byte write with SMBus functions
	r = i2c_smbus_write_byte(fd, buf);
	if(r < 0)
		fprintf(stderr, "Error i2c_write_1b: %s\n", strerror(errno));
	usleep(10);
	return r;
}

int AD7997::i2c_write_2b(int fd, unsigned char buf[2])
{
	int r;
	// we must simulate a plain I2C byte write with SMBus functions
	r = i2c_smbus_write_byte_data(fd, buf[0], buf[1]);
	if(r < 0)
		fprintf(stderr, "Error i2c_write_2b: %s\n", strerror(errno));
	usleep(10);
	return r;
}

int AD7997::i2c_write_3b(int fd, unsigned char buf[3])
{
	int r;
	// we must simulate a plain I2C byte write with SMBus functions
	// the __u16 data field will be byte swapped by the SMBus protocol
	r = i2c_smbus_write_word_data(fd, buf[0], buf[2] << 8 | buf[1]);
	if(r < 0)
		fprintf(stderr, "Error i2c_write_3b: %s\n", strerror(errno));
	usleep(10);
	return r;
}
