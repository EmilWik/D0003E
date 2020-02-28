
#include <avr/io.h>
#include "TinyTimber.h"
#include "SimWriter.h"
#include "CarQueue.h"
#include "Bridge.h"


typedef struct {
	Object super;
	CarQueue *northQueue;
	CarQueue *southQueue;
	Bridge *bridge;
} InputHandler;


/*

Bit 0: Northbound car arrival sensor activated
Bit 1: Northbound bridge entry sensor activated
Bit 2: Southbound car arrival sensor activated
Bit 3: Southbound bridge entry sensor activated

*/

void carsUpdate(InputHandler *self){
	
	#define SOUTHBOUND_CAR	"s"
	#define NORTHBOUND_CAR	"n"
	#define EXIT			"e"
	
	if ( UDR0 == SOUTHBOUND_CAR ) {
		ASYNC(&northQueue, addCar, NULL);
	}
	
	if ( UDR0 == NORTHBOUND_CAR ) {
		ASYNC(&southQueue, addCar, NULL);
	}
	
	if ( UDR0 == EXIT ) {
		//TODO Exit the simulator.
	}
}
