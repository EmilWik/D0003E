
#ifndef PULSEGENERATOR_H_
#define PULSEGENERATOR_H_

#include "TinyTimber.h"
#include "PortWriter.h"
#include "GUI.h"

typedef struct {
	Object super;
	PortWriter *pWriter;
	GUI *gui;
	int pin, frequency, savedFreq;
	int isHigh;
} PulseGenerator;

//      Initialization macro for class Object.
#define initPulseGenerator(portWriter, gui, PIN) \
		{initObject(), portWriter, gui, PIN, 0, 0, 0}



void increaseFrequency(PulseGenerator *self, int amount);

void saveOrLoadFrequency(PulseGenerator *self);

void generatePulse(PulseGenerator *self);


#endif /* PULSEGENERATOR_H_ */