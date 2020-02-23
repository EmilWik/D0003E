
#ifndef PULSEGENERATOR_H_
#define PULSEGENERATOR_H_

#include "TinyTimber.h"
#include "PortWriter.h"

typedef struct {
	Object super;
	PortWriter *pWriter;
	int pin, frequency, savedFreq;
	int isHigh;
} PulseGenerator;

//      Initialization macro for class Object.
#define initPulseGenerator(portWriter, PIN) \
		{initObject(), portWriter, PIN, 0, 0, 0}



void increaseFrequency(PulseGenerator *self, int amount);

void saveOrLoadFrequency(PulseGenerator *self);

void generatePulse(PulseGenerator *self, int bl);


#endif /* PULSEGENERATOR_H_ */