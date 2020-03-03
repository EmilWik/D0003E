#include <pthread.h>
#include <stdio.h>
#include <fcntl.h>
#include <termios.h>
#include <stdint.h>



int com1;

int northGreen = 0;
int southGreen = 0;
int northRed = 0;
int southRed = 0;
int northCars = 0;
int southCars = 0;


pthread_t trafficLight_t;
pthread_t gui_t;
pthread_t bridge_t;





void openSerialPort(void) {

	com1 = open("/dev/ttyS0", O_RDWR);
	if (com1 < 0) {
		printf("Can't open file! \n");
	}


	struct termios termios_p;
	if (tcgetattr(com1, &termios_p)) {
		printf("Could not get termios attributes. (openSerialPort)\n");
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
	int text = write(*com1, &instruction, sizeof(instruction));

	if (text < 0) {
		printf("Could not write instruction to avr! \n");
	}
}



void trafficLight(void) {
	uint8_t recieved;
	while (1) {
		int signal = read(com1, &recieved, sizeof(recieved));
		northGreen = signal & (1 << 0);
		northRed = signal & (1 << 1);
		southGreen = signal & (1 << 2);
		southRed = signal & (1 << 3);
	}
}



int input(void) {
	fd_set rfds;
	fcntl(fileno(stdin), F_SETFL, O_NONBLOCK); // open stdin 

	struct termios termios_p;
	tcgetattr(STDIN_FILENO, &termios_p);
	termios_p.c_lflag &= ~(ICANON | ECHO);
	termios_p.c_cc[VMIN] = 1;
	tcsetattr(STDIN_FILENO, TCSANOW, &termios_p);

	FD_SET(0, &rfds); // use keyboard

	while (1) {
		if (FD_ISSET(0, &rfds)) { // handle keypress
			char ch = getchar();

			swich(ch) {

				case 'n':
					writeToAVR(0x1);
					northCars++;
					break;

				case 's':
					writeToAVR(0x4);
					southCars++;
					break;

				case 'e':
					return 0;
					break;

				default:
					break;

			}

		}

	}

	return 0;
}

void *GUI(void *a);
void *bridge();

int main() {


	openSerialPort(&com1);
	pthread_create(&trafficLight_t, NULL, trafficLight, NULL); // thread, attributes, method and argument
	pthread_create(&gui_t, NULL, GUI, NULL); // thread, attributes, method and argument
	pthread_create(&bridge_t, NULL, bridge, 0);

	return input();
}


