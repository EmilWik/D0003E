#include <avr/io.h>
#include <stdbool.h>
#include "TinyTimber.h"
#include "GUI.h"
#include "PulseGenerator.h"


typedef struct {
	Object super;
	PulseGenerator *pGen[2];
	GUI *gui;
	bool risingEdge;
} InputHandler;





void initialize(InputHandler *self){
	SYNC(self->gui, initLCD, NULL);
	ASYNC(self->pGen[0], generatePulse, NULL);
	ASYNC(self->pGen[1], generatePulse, NULL);
}





void joystickCrossways(InputHandler *self){
	
	
	#define SELECTED_PGEN self->pGen[self->gui->focus] 
	#define P4 (1<<PINB4)
	#define P6 (1<<PINB6)
	#define P7 (1<<PINB7)
	#define repPeriod 450

	
	
	// Depressed
	if(!(PINB-P6-P7)){
		ASYNC(SELECTED_PGEN, saveOrLoadFrequency, NULL);

	}
	
	// Up
	if(!(PINB-P4-P7)){
		AFTER(MSEC(repPeriod), SELECTED_PGEN, increaseFrequency, 1);

	}
	
	// Down
	if(!(PINB-P4-P6)){
		AFTER(MSEC(repPeriod), SELECTED_PGEN, increaseFrequency, -1);

	}
	
	
	
}



void joystickSideways(InputHandler *self, int arg){
	
	if(self->risingEdge){
		self->risingEdge = false;
		ASYNC(self->gui, switchFocus, arg);
	}else{
		self->risingEdge = true;
	}
	
}


