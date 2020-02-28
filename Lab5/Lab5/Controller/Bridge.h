
#ifndef BRIDGE_H_
#define BRIDGE_H_

#include "TinyTimber.h"
#include "SimWriter.h"



typedef struct {
	Object super;
	SimWriter *simWriter;
	int carsOnBridge;
} Bridge;



#define initBridge(simWriter) \
{ initObject(), simWriter, 0}


void addCarToBridge(Bridge *self);





#endif /* BRIDGE_H_ */