
#ifndef PORTWRITER_H_
#define PORTWRITER_H_

typedef struct {
	Object super;
} PortWriter;

//      Initialization macro for class Object.
#define initPortWriter() \
		{ initObject()}


void writeToPin(int value, int pin);


#endif /* PORTWRITER_H_ */