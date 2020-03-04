
#include "TinyTimber.h"
#include "GUI.h"
#include "Bridge.h"




typedef struct {
	Object super;
	Bridge *bridge;
	GUI *gui;
	int carsInQueue;
	int dirr;
} CarQueue;


enum Direction{ North, South};


void updateGUI(CarQueue *self){
	
	switch(self->dirr){
		case North:
			ASYNC(self->gui, carsInNorthQueue, self->carsInQueue);
		break;
		
		case South:
			ASYNC(self->gui, carsInSouthQueue, self->carsInQueue);
		break;
		
		default: /* ¯\_(?)_/¯ */ break;
	}
}


void addCar(CarQueue *self){
	++(self->carsInQueue);
	ASYNC(self, updateGUI, NULL);
}



void sendCar(CarQueue *self){
	if(self->carsInQueue > 0){
		--(self->carsInQueue);
		ASYNC(self->bridge, addCarToBridge, NULL);
	}
	
	ASYNC(self, updateGUI, NULL);
}

