


#ifndef SIMWRITER_H_
#define SIMWRITER_H_

#include "TinyTimber.h"


typedef struct {
	Object super;
	int nG;
	int nR;
	int sG;
	int sR;
} SimWriter;



#define initSimWriter() \
	{ initObject(), 0, 0, 0, 0}



void northboundGreenLight(SimWriter *self);

void northboundRedLight(SimWriter *self);

void southboundGreenLight(SimWriter *self);

void southboundRedLight(SimWriter *self);


#endif /* SIMWRITER_H_ */