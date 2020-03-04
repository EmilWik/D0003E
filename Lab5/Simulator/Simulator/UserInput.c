#include "globals.h"
#include "SerialPort.h"
#include <stdint.h>
#include <fcntl.h>
#include <termios.h>


int input(void) {
	fd_set rfds;
	fcntl(fileno(stdin), F_SETFL, O_NONBLOCK); // open stdin 

	struct termios termios_p;
	tcgetattr(STDIN_FILENO, &termios_p);
	termios_p.c_lflag &= ~(ICANON | ECHO);
	termios_p.c_cc[VMIN] = 1;
	tcsetattr(STDIN_FILENO, TCSANOW, &termios_p);

	FD_SET(0, &rfds); // use keyboard




	#define NORTHBOUND_CAR_ARRIVE 0x1	
	#define SOUTHBOUND_CAR_ARRIVE 0x4	

	while (1) {

		if (FD_ISSET(0, &rfds)) { // handle keypress
			char ch = getchar();

			switch (ch) {			// Du hade bara glömt ett 't' i ordet 'switch'

			case 'n':
				++northCars;
				writeToAVR(NORTHBOUND_CAR_ARRIVE);
				break;

			case 's':
				++southCars;
				writeToAVR(SOUTHBOUND_CAR_ARRIVE);
				break;

			case 'e':
				return 0;
				break;

			default: /* ¯\_(?)_/¯ */ break;
			}
		}
	}

	return 0;
}
