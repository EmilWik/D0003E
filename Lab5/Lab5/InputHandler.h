

#ifndef INPUTHANDLER_H_
#define INPUTHANDLER_H_

#include "TinyTimber.h"
#include "SimWriter.h"
#include "CarQueue.h"
#include "Bridge.h"


typedef struct {
	Object super;
	CarQueue *northQueue;
	CarQueue *southQueue;
	Bridge *bridge;
} InputHandler;


#define initInputHandler(southQueue, northQueue, bridge) { initObject(), northQueue, southQueue, bridge}
	
void test(InputHandler *self);



#endif /* INPUTHANDLER_H_ */