#include "UserInput.h"
#include "SerialPort.h"
#include "GUI.h"
#include "Simulator.h"
#include <pthread.h>



pthread_t getLights_t;
pthread_t gui_t;
pthread_t simulator_t;


int main() {

	openSerialPort();

	pthread_create(&getLights_t, NULL, getLights, NULL);	// Keeps the lights up to date
	pthread_create(&gui_t,		 NULL, GUI,		  NULL);	// Keeps the GUI up to date
	pthread_create(&simulator_t, NULL, simulator, NULL);	// Sends cars to the bridge

	return input();
}


