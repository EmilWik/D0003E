


#include "TinyTimber.h"
#include "GUI.h"




typedef struct {
	Object super;
	GUI *gui;
	int carsOnBridge;
} Bridge;




void removeCarFromBridge(Bridge *self){
	--(self->carsOnBridge);
	ASYNC(self->gui, carsOnBridge, self->carsOnBridge);
}


void addCarToBridge(Bridge *self){
	++(self->carsOnBridge);
	ASYNC(self->gui, carsOnBridge, self->carsOnBridge);
	
	
	#define TRAVEL_TIME 5
	
	AFTER(SEC(TRAVEL_TIME), self, removeCarFromBridge, NULL);
}

