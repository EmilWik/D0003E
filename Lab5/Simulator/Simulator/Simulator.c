#include "globals.h"		// northCars, southCars
#include "SerialPort.h"		// writeToAVR
#include <stdio.h>			// fflush
#include <unistd.h>			// usleep
#include <pthread.h>



void* driveOverBridge(void *arg) {
	#define DRIVE_TIME 5000000			// 5s

	++bridgeCars;
	usleep(DRIVE_TIME);
	--bridgeCars;

	pthread_exit(0);
}



void* simulator(void* arg) {

	#define NORTHBOUND_BRIDGE_ENTRY	0x2	
	#define SOUTHBOUND_BRIDGE_ENTRY	0x8	
	#define WAIT_TIME 1000000			// 1s


	while (1) {

		while (northGreen && (northCars > 0)) {
			--northCars;
			
			pthread_t car_t;
			pthread_create(&car_t, NULL, driveOverBridge, NULL);


			writeToAVR(NORTHBOUND_BRIDGE_ENTRY);
			usleep(WAIT_TIME);
		}

		while (southGreen && (southCars > 0)) {
			--southCars;

			pthread_t car_t;
			pthread_create(&car_t, NULL, driveOverBridge, NULL);

			writeToAVR(SOUTHBOUND_BRIDGE_ENTRY);
			usleep(WAIT_TIME);
		}

		/* Do nothing if both lights are red */


		fflush(stdin);
	}

}