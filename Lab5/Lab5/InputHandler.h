

#ifndef INPUTHANDLER_H_
#define INPUTHANDLER_H_

#include "TinyTimber.h"
#include "SimWriter.h"
#include "CarQueue.h"
#include "Bridge.h"


typedef struct {
	Object super;
	GUI *gui;
	CarQueue *northQueue;
	CarQueue *southQueue;
	Bridge *bridge;
} InputHandler;


#define initInputHandler(gui, bridge, southQueue, northQueue) { initObject(), gui,northQueue, southQueue, bridge}
	
void readInput(InputHandler *self);



#endif /* INPUTHANDLER_H_ */