


#include "TinyTimber.h"
#include "SimWriter.h"

#define TRAVEL_TIME 5


typedef struct {
	Object super;
	SimWriter *simWriter;
	int carsOnBridge;
} Bridge;




void removeCarFromBridge(Bridge *self){
	--(self->carsOnBridge);
	ASYNC(self, carsOnBridge, self->carsOnBridge);
}


void addCarToBridge(Bridge *self){
	++(self->carsOnBridge);
	ASYNC(self, carsOnBridge, self->carsOnBridge);
	AFTER(SEC(TRAVEL_TIME), self, removeCarFromBridge, NULL);
}

