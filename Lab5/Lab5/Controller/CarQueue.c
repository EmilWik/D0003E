

#include "TinyTimber.h"
#include "SimWriter.h"
#include "Bridge.h"





enum Dirr{
	North = 0;
	South = 1;
};

typedef struct {
	Object super;
	Bridge *bridge;
	SimWriter *simWriter;
	int carsInQueue;
	int dirr;
} CarQueue;




/*
void updateSimWriter(CarQueue *self){
	
	switch(self->dirr){
		case Dirr.North:
			ASYNC(self->simWriter, carsInNorthQueue, self->carsInQueue)
		break;
		
		case Dirr.South:
			ASYNC(self->simWriter, carsInSouthQueue, self->carsInQueue)
		break;
		
		default:
		break;
	}
}
*/

void addCar(CarQueue *self){
	++(self->carsInQueue);
	//ASYNC(self, updateSimWriter, NULL);
}



void sendCar(CarQueue *self){
	if(self->carsInQueue > 0){
		--(self->carsInQueue);
		//ASYNC(self->bridge, addCarToBridge, NULL)
	}
	
	//ASYNC(self, updateSimWriter, NULL);
}

