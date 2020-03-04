#include "globals.h"	// com1, northGreen, southGreen, northRed, southRed
#include <stdint.h>		// uint8_t
#include <termios.h>
#include <fcntl.h>
#include <stdio.h>		


void openSerialPort(void) {

	com1 = open("/dev/ttyS0", O_RDWR);
	if (com1 < 0) {
		printf("Can't open file! \n");
	}


	struct termios termios_p;
	if (tcgetattr(com1, &termios_p)) {
		printf("Couldn't get termios attributes! \n");
		exit(-1);
	}


	tcflush(com1, TCIFLUSH); //Flush COM1 recieved data that is not read
	//Baud rate(signal changes per second) = 9600 | Character size mask 8 | Set two stop bits rather than one | Enable receiver | Ignore modem control lines | Lower modem control lines after last process closes the device (hang up) | Enable input parity checking
	termios_p.c_cflag = B9600 | CS8 | CSTOPB | CREAD | CLOCAL | HUPCL | INPCK;
	// NOT (Echo input characters | echo the NL character even if ECHO is not set)
	termios_p.c_lflag &= ~(ECHO | ECHONL | ICANON);
	// Avoid inter-message overlap.
	termios_p.c_cc[VTIME] = 10;
	termios_p.c_cc[VMIN] = 1;
	cfsetispeed(&termios_p, B9600);
	cfsetospeed(&termios_p, B9600);


	if (tcsetattr(com1, TCSANOW, &termios_p)) {
		printf("Could not set termios attributes! \n");
		exit(-1);
	}
}



void writeToAVR(uint8_t instruction) {
	int text = write(com1, &instruction, sizeof(instruction));

	if (text < 0) {
		printf("Couldn't write instruction to avr! \n");
	}

}



void getLights(void) {
	uint8_t recieved;

	while (1) {
		int signal = read(com1, &recieved, sizeof(recieved));

		northGreen	= signal & (1 << 0);
		northRed	= signal & (1 << 1);
		southGreen	= signal & (1 << 2);
		southRed	= signal & (1 << 3);
	}
}