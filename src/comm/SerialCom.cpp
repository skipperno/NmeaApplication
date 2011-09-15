/*
 * SerialCom.cpp
 *
 *  Created on: Sep 1, 2011
 *      Author: ernad
 */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>


#include "SerialCom.h"

SerialCom::SerialCom() {
	// TODO Auto-generated constructor stub

}

SerialCom::~SerialCom() {
	// TODO Auto-generated destructor stub
}


int SerialCom::openSerial(const char* portName, int baudRate)
{
        struct termios tio;
        struct termios stdio;
        //int tty_fd;
        //fd_set rdset;
        int bRate;

        if (baudRate == 4800)
        	bRate = B4800;
        else if (baudRate == 9600)
        	bRate = B9600;
        else if (baudRate == 38400)
            bRate = B38400;
        else if (baudRate == 115200)
        	bRate = B115200;

       // unsigned char c='D';

       // printf("Please start with %s /dev/ttyS1 (for example)\n",argv[0]);
        memset(&stdio,0,sizeof(stdio));
        stdio.c_iflag=0;
        stdio.c_oflag=0;
        stdio.c_cflag=0;
        stdio.c_lflag=0;
        stdio.c_cc[VMIN]=1;
        stdio.c_cc[VTIME]=0;
        tcsetattr(STDOUT_FILENO,TCSANOW,&stdio);
        tcsetattr(STDOUT_FILENO,TCSAFLUSH,&stdio);
        //TODO: ernad: skal den kommenteres vekk? non-block ligger i denne linje og nede i "open"
      //  fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);       // make the reads non-blocking

        memset(&tio,0,sizeof(tio));
        tio.c_iflag=0;
        tio.c_oflag=0;
        tio.c_cflag=CS8|CREAD|CLOCAL;           // 8n1, see termios.h for more information
        tio.c_lflag=0;
        tio.c_cc[VMIN]=1;
        tio.c_cc[VTIME]=5;

        tty_fd=open(portName, O_RDWR );//| O_NONBLOCK);

        cfsetospeed(&tio,bRate); //B4800);//B115200);            // 115200 baud
        cfsetispeed(&tio,bRate); //B4800);//B115200);            // 115200 baud

        tcsetattr(tty_fd,TCSANOW,&tio);
     /*   while (c!='q')
        {
                if (read(tty_fd,&c,1)>0)        write(STDOUT_FILENO,&c,1);              // if new data is available on the serial port, print it out
                else
                	printf("!!!!!!!!!!read 0 bytes\n");
             //   if (read(STDIN_FILENO,&c,1)>0)  write(tty_fd,&c,1);                     // if new data is available on the console, send it to the serial port
                usleep(30000);
        }

        close(tty_fd);*/

        printf("Serial port: %s is open. Baud rate: %d\n", portName, baudRate);

        return 1;
}

int SerialCom::receiveSerial(char* pBuffer, int maxLength) {
	int nLen;
	//*length = 0;

		nLen=read(tty_fd, pBuffer, maxLength); //inpstream.readsome(pBuffer, 10023);
		//printf("rec: %d\n", nLen);
		return nLen;
		/*if (nLen > 0) {
			*length=nLen;
			pBuffer[*length] =0;
		} else
			return;*/
}


void SerialCom::closeSerial(){
	close(tty_fd);
}

