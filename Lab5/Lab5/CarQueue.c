

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





void updateGUI(CarQueue *self){
	
	
	switch(self->dirr){
		case 0:
			ASYNC(self->gui, carsInNorthQueue, self->carsInQueue);
		break;
		
		case 1:
			ASYNC(self->gui, carsInSouthQueue, self->carsInQueue);
		break;
		
		default:
		break;
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

