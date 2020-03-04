#include "globals.h"
#include <stdio.h>		// printf
#include <unistd.h>		// usleep


void* GUI(void* arg) {

	#define REFRESH_TIME 100000			// 100ms
	#define CLEAR_TERMINAL "\033[2J"


	while (1) {
		
		printf(CLEAR_TERMINAL);


		
		printf("\n #-------------| Cars |-------------# \n");
		printf("Northbound cars in queue: %d \n", southCars);
		printf("Southbound cars in queue: %d \n", northCars);
		printf("Cars on bridge: %d \n", bridgeCars);


		printf("\n #------------| Lights |------------# \n");
		printf("North	Green: %d	Red: %d \n", northGreen, northRed);
		printf("South	Green: %d	Red: %d \n", southGreen, southRed);


		
		usleep(REFRESH_TIME);
	}
}