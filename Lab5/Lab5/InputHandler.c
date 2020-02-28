
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
	
	
	
	
	#define NORTHBOUND_CAR_ARRIVE	"0"
	#define NORTHBOUND_BRIDGE_ENTRY	"1"
	#define SOUTHBOUND_CAR_ARRIVE	"2"
	#define SOUTHBOUND_BRIDGE_ENTRY	"3"
	
	
	if ( UDR0 == NORTHBOUND_CAR_ARRIVE ) {
		ASYNC(self->northQueue, addCar, NULL);
	}
	
	if ( UDR0 == NORTHBOUND_BRIDGE_ENTRY ) {
		ASYNC(self->northQueue, sendCar, NULL);
	}
	
	if ( UDR0 == SOUTHBOUND_CAR_ARRIVE ) {
		ASYNC(self->southQueue, addCar, NULL);
	}
	
	
	if ( UDR0 == SOUTHBOUND_BRIDGE_ENTRY ) {
		ASYNC(self->southQueue, sendCar, NULL);
	}
	

}
