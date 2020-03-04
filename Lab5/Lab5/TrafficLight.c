
#include "TinyTimber.h"
#include "SimWriter.h"

#include <avr/io.h>

typedef struct {
	Object super;
	SimWriter *simWriter;
	int focus;
} TrafficLight;



static enum Direction{ North, South};
	

void trafficLightFunc(TrafficLight* self){
	
	
	switch(self->focus){
		case North:
			SYNC(self->simWriter, southboundRedLight, NULL);
			AFTER(SEC(5),self->simWriter, northboundGreenLight, NULL);
		break;
		
		case South:
			SYNC(self->simWriter, northboundRedLight, NULL);
			AFTER(SEC(5), self->simWriter, southboundGreenLight, NULL);
		break;
		
		default:
		break;
	}
	
	
	self->focus = !self->focus;
	
	
	#define ON_TIME 8	// Time light is green
	
	AFTER(SEC(ON_TIME + 5), self, trafficLightFunc, NULL);
	
	
	
	
	
	
	
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