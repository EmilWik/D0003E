#include "TinyTimber.h"
#include "PortWriter.h"
#include <stdbool.h>

typedef struct {
	Object super;
	PortWriter *pWriter;
	int pin, frequency, savedFreq;
	bool isHigh;
} PulseGenerator;



void increaseFrequency(PulseGenerator *self, int amount){
	
	self->frequency += amount;
	
	if(self->frequency < 0) { self->frequency =  0; }
	if(self->frequency > 99){ self->frequency = 99; }
}


void saveOrLoadFrequency(PulseGenerator *self){
	
	if (self->frequency == 0)
	{
		self->frequency = self->savedFreq;
	}
	else{
		self->savedFreq = self->frequency; 
	}
	
}


void generatePulse(PulseGenerator *self, int bl){
	self->isHigh = !self->isHigh;
	int temp[] = {self->isHigh, self->pin};
	ASYNC(self->pWriter, writeToPin, temp);
	
	int msec = bl+self->frequency*500;
	AFTER(MSEC(msec), self, generatePulse, msec);	
}
