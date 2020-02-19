
#ifndef PULSEGENERATOR_H_
#define PULSEGENERATOR_H_

typedef struct {
	Object super;
	Timer timer;
	int pin, LCDPosition;
} PulseGenerator;

//      Initialization macro for class Object.
#define initPulseGenerator(pin, LCDPosition) \
		{initObject(), initTimer(), pin, LCDPosition}



void increaseFrequency(int amount);


void saveFrequency(int frequency);


void loadFrequency();


#endif /* PULSEGENERATOR_H_ */