
#ifndef INPUTHANDLER_H_
#define INPUTHANDLER_H_

#include "TinyTimber.h"
#include "GUI.h"
#include "PulseGenerator.h"

typedef struct {
	Object super;
	PulseGenerator pGen1, pGen2;
	GUI gui;
} InputHandler;


//      Initialization macro for class Object.
#define initInputHandler(PulseGenerator1, PulseGenerator2, gui) \
		{ NULL, NULL, PulseGenerator1, PulseGenerator2, gui};



void joystickUp();

void joystickDown();

void joystickSideways();

void joystickPressed();


#endif /* INPUTHANDLER_H_ */