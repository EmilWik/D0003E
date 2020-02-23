#include <avr/io.h>
#include "TinyTimber.h"

typedef struct {
	Object super;
} PortWriter;


void writeToPin(PortWriter *self, int args[]){
	PINE = (args[0] << args[1]);
}
