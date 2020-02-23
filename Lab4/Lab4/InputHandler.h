
#ifndef INPUTHANDLER_H_
#define INPUTHANDLER_H_

#include "TinyTimber.h"
#include "GUI.h"
#include "PulseGenerator.h"

typedef struct {
	Object super;
	PulseGenerator *pGen[2];
	GUI *gui;
	int risingEdge;
} InputHandler;


//      Initialization macro for class Object.
#define initInputHandler(gui, pGen1, pGen2) \
		{ initObject(), {pGen1, pGen2}, gui, 1}



void joystickCrossways(InputHandler *self);		// Up, Down & Depressed

void joystickSideways(InputHandler *self, int arg);		// Left & Right

void initialize(InputHandler *self);


#endif /* INPUTHANDLER_H_ */