
#ifndef PORTWRITER_H_
#define PORTWRITER_H_

#include "TinyTimber.h"

typedef struct {
	Object super;
} PortWriter;


//      Initialization macro for class Object.
#define initPortWriter() \
		{ initObject()}


void writeToPin(PortWriter *self, int args[2]);


#endif /* PORTWRITER_H_ */