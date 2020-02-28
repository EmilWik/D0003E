

#ifndef CARQUEUE_H_
#define CARQUEUE_H_





#include "TinyTimber.h"
#include "SimWriter.h"
#include "Bridge.h"





enum Dirr{
	North = 0;
	South = 1;
	};

typedef struct {
	Object super;
	Bridge *bridge;
	SimWriter *simWriter;
	int carsInQueue;
	int dirr;
} CarQueue;


#define initCarQueue(bridge, simWriter) \
{ initObject(), bridge, simWriter, 0, Dirr.North}


void addCar(CarQueue *self);


void sendCar(CarQueue *self);



#endif /* CARQUEUE_H_ */