

#include "TinyTimber.h"
#include <avr/io.h>

typedef struct {
	Object super;
	int nG = 0;
	int nR = 0;
	int sG = 0;
	int sR = 0;
} SimWriter;



/*

Bit 0: Northbound green light status
Bit 1: Northbound red light status
Bit 2: Southbound green light status
Bit 3: Southbound red light status

*/


void write(SimWriter *self){
	while ((UCSR0A & (1 << UDRE0)) == 0) {}; // Do nothing until UDR is ready for more data to be written to it
	UDR0 = (self->nG << 0) | (self->nR << 1) |( self->sG << 2) | (self->sR << 3); // Echo back the received byte back to the computer
}



void northboundGreenLight(SimWriter *self){
	self->nG = 1;
	self->nR = 0;
	ASYNC(self, write, NULL);
}

void northboundRedLight(SimWriter *self){
	self->nG = 0;
	self->nR = 1;
	ASYNC(self, write, NULL);
}

void southboundGreenLight(SimWriter *self){
	self->sG = 1;
	self->sR = 0;
	ASYNC(self, write, NULL);
}

void southboundRedLight(SimWriter *self){
	self->sG = 0;
	self->sR = 1;
	ASYNC(self, write, NULL);
}


