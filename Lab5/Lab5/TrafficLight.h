

#ifndef TRAFFICLIGHT_H_
#define TRAFFICLIGHT_H_

#include "TinyTimber.h"
#include "SimWriter.h"
//#include "CarQueue.h"


typedef struct {
	Object super;
	SimWriter *simWriter;
	int focus;
} TrafficLight;


#define initTrafficLight(simWriter) { initObject(), simWriter, 0}

//void greenLight(TrafficLight* self);
	
//void switchFocus(TrafficLight* self);

void trafficLightFunc(TrafficLight* self);


#endif /* TRAFFICLIGHT_H_ */