#include <avr/io.h>
#include "TinyTimber.h"
#include "SimWriter.h"
#include "CarQueue.h"
#include "Bridge.h"


typedef struct {
	Object super;
	GUI *gui;
	CarQueue *northQueue;
	CarQueue *southQueue;
} InputHandler;


/*

Bit 0: Northbound car arrival sensor activated
Bit 1: Northbound bridge entry sensor activated
Bit 2: Southbound car arrival sensor activated
Bit 3: Southbound bridge entry sensor activated

*/



void readInput(InputHandler *self){
	
	char ReceivedByte = UDR0; // Fetch the received byte value into the variable "ByteReceived"
	

	#define NORTHBOUND_CAR_ARRIVE	ReceivedByte & (1 << 0)		// 1
	#define NORTHBOUND_BRIDGE_ENTRY	ReceivedByte & (1 << 1)		// 2 
	#define SOUTHBOUND_CAR_ARRIVE	ReceivedByte & (1 << 2)		// 4
	#define SOUTHBOUND_BRIDGE_ENTRY	ReceivedByte & (1 << 3)		// 8


	
	if (NORTHBOUND_CAR_ARRIVE)	{ ASYNC(self->northQueue,  addCar, NULL); }
	if (NORTHBOUND_BRIDGE_ENTRY){ ASYNC(self->northQueue, sendCar, NULL); }		
	if (SOUTHBOUND_CAR_ARRIVE)	{ ASYNC(self->southQueue,  addCar, NULL); }
	if (SOUTHBOUND_BRIDGE_ENTRY){ ASYNC(self->southQueue, sendCar, NULL); }
	
}

/*
	while ((UCSR0A & (1 << UDRE0)) == 0) {}; // Do nothing until UDR is ready for more data to be written to it
	UDR0 = ReceivedByte; // Echo back the received byte back to the computer
*/