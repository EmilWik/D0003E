
#ifndef GUI_H_
#define GUI_H_

#include "TinyTimber.h"

typedef struct {
	Object super;
	int focus;
} GUI;

//      Initialization macro for class Object.
#define initGUI() \
		{ initObject(), 0}

void initLCD();			

// Prints the 2 digit number to the LCD
void printAt(GUI *self, int num);

// Changes the indicator that shows which of the two pulse generators that is currently receiving user input
void switchFocus(GUI *self);


#endif /* GUI_H_ */