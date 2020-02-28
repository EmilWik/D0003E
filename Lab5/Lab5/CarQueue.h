

#ifndef CARQUEUE_H_
#define CARQUEUE_H_





#include "TinyTimber.h"
#include "SimWriter.h"
#include "Bridge.h"






typedef struct {
	Object super;
	Bridge *bridge;
	GUI *gui;
	int carsInQueue;
	int dirr;
} CarQueue;


#define initCarQueue(bridge, simWriter, dirr) \
{ initObject(), bridge, simWriter, 0, dirr}


void addCar(CarQueue *self);


void sendCar(CarQueue *self);



#endif /* CARQUEUE_H_ */