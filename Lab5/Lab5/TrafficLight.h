

#ifndef TRAFFICLIGHT_H_
#define TRAFFICLIGHT_H_

#include "TinyTimber.h"
#include "SimWriter.h"
//#include "CarQueue.h"


typedef struct {
	Object super;
	SimWriter *simWriter;
	//CarQueue *carQueue[2];
	int focus;
} TrafficLight;


#define initTrafficLight(simWriter, southQueue, northQueue) { initObject(), simWriter, /*{northQuue, southQueue},*/ 0}

//void greenLight(TrafficLight* self);
	
//void switchFocus(TrafficLight* self);

void trafficLight(TrafficLight* self);



#endif /* TRAFFICLIGHT_H_ */