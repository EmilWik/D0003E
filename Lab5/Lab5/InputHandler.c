
#include <avr/io.h>
#include "TinyTimber.h"
#include "SimWriter.h"
#include "CarQueue.h"
#include "Bridge.h"


typedef struct {
	Object super;
	CarQueue *northQueue;
	CarQueue *southQueue;
} InputHandler;


/*

Bit 0: Northbound car arrival sensor activated
Bit 1: Northbound bridge entry sensor activated
Bit 2: Southbound car arrival sensor activated
Bit 3: Southbound bridge entry sensor activated

*/

/*
	void realFunc()...
*/






void test(InputHandler *self){
	
	
	while (!(UCSR0A & (1<<RXC0)));  // Do nothing until data have been received and is ready to be read from UDR
	char ReceivedByte = UDR0;
	
	
	#define NORTHBOUND_CAR_ARRIVE	"0"
	#define NORTHBOUND_BRIDGE_ENTRY	"1"
	#define SOUTHBOUND_CAR_ARRIVE	"2"
	#define SOUTHBOUND_BRIDGE_ENTRY	"3"
	
	
	if ( ReceivedByte == NORTHBOUND_CAR_ARRIVE ) {
		ASYNC(self->northQueue, addCar, NULL);
	}
	
	if ( ReceivedByte == NORTHBOUND_BRIDGE_ENTRY ) {
		ASYNC(self->northQueue, sendCar, NULL);
	}
	
	if ( ReceivedByte == SOUTHBOUND_CAR_ARRIVE ) {
		ASYNC(self->southQueue, addCar, NULL);
	}
	
	
	if ( ReceivedByte == SOUTHBOUND_BRIDGE_ENTRY ) {
		ASYNC(self->southQueue, sendCar, NULL);
	}
	

}
