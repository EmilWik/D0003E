#include <avr/io.h>
#include <stdbool.h>
#include "TinyTimber.h"
#include "PortWriter.h"
#include "GUI.h"


typedef struct {
	Object super;
	PortWriter *pWriter;
	GUI *gui;
	int pin, frequency, savedFreq;
	bool isHigh;
} PulseGenerator;



void increaseFrequency(PulseGenerator *self, int amount){
	
	self->frequency += amount;
	
	if(self->frequency < 0) { self->frequency =  0; }
	if(self->frequency > 99){ self->frequency = 99; }
		
	
	ASYNC(self->gui, printAt, self->frequency);
		
		
	#define P4 (1<<PINB4)
	#define P6 (1<<PINB6)
	#define P7 (1<<PINB7)
	#define repPeriod 150
	
	
	// Up
	if(!(PINB-P4-P7)){
		AFTER(MSEC(repPeriod), self, increaseFrequency, amount);		// For holding down button
	}
	
	// Down
	if(!(PINB-P4-P6)){
		AFTER(MSEC(repPeriod), self, increaseFrequency, amount);		// For holding down button
	}
	
}


void saveOrLoadFrequency(PulseGenerator *self){
	
	if (self->frequency == 0)
	{
		self->frequency = self->savedFreq;
	}
	else{
		self->savedFreq = self->frequency; 
	}
	
	
	ASYNC(self->gui, printAt, self->frequency);
}


void generatePulse(PulseGenerator *self){
	
	if(self->frequency == 0){
		self->isHigh = 0;
		
		AFTER(MSEC(500), self, generatePulse, NULL);
	}
	else{
		self->isHigh = !self->isHigh;
			
		AFTER(MSEC(self->frequency*500), self, generatePulse, NULL);	
	}
	
	int temp[] = {self->isHigh, self->pin};
	ASYNC(self->pWriter, writeToPin, temp);
}
