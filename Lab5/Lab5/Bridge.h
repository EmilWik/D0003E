
#ifndef BRIDGE_H_
#define BRIDGE_H_

#include "TinyTimber.h"
#include "GUI.h"



typedef struct {
	Object super;
	GUI *gui;
	int carsOnBridge;
} Bridge;



#define initBridge(gui) \
{ initObject(), gui, 0}


void addCarToBridge(Bridge *self);





#endif /* BRIDGE_H_ */