
#include "TinyTimber.h"
#include "SimWriter.h"
//#include "CarQueue.h"

typedef struct {
	Object super;
	SimWriter *simWriter;
	//CarQueue *carQueue[2];
	int focus;
} TrafficLight;


enum Dirr{
	North = 0;
	South = 1;
};

/*
void greenLight(TrafficLight* self){
	ASYNC(self->carQueue[self->focus], sendCar, NULL);
}
*/

/*
void switchFocus(TrafficLight* self){
	self->focus = !self->focus;
}
*/


void trafficLight(TrafficLight* self){
	
	switch(self->focus){
		case Dirr.North:
			SYNC(self->simWriter, southboundRedLight, NULL);
			AFTER(SEC(5),self->simWriter, northboundGreenLight, NULL);
		break;
		
		case Dirr.South:
			SYNC(self->simWriter, northboundRedLight, NULL);
			AFTER(SEC(5), self->simWriter, southboundGreenLight, NULL);
		break;
		
		default:
		break;
	}
	
	
	self->focus = !self->focus;
	
	
	#define ON_TIME 5	// Time light is green
	
	AFTER(SEC(ON_TIME), self->simWriter, southboundGreenLight, NULL);
	
	
	
	
	
	
	
	/*
	#define CARS_TO_SEND 5		//Number of times traffic light will turn green at one side before switching side.
	
	int i;
	for (i = 0; i < 5; i++) {
		AFTER(SEC(i), self, greenLight, NULL);
	}
	SYNC(self, switchFocus, NULL);
	AFTER(SEC(i+5), self, trafficLight, NULL);
	*/
	
}



// Simulatorn tar hand om time:ingen