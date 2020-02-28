
#ifndef GUI_H_
#define GUI_H_

#include "TinyTimber.h"

typedef struct {
	Object super;
} GUI;

//      Initialization macro for class Object.
#define initGUI() \
		{ initObject()}

void initLCD();			

// Prints the 2 digit number to the LCD
void printAt(GUI *self, int num);



void carsOnBridge(GUI *self, int amount);

void carsInNorthQueue(GUI *self, int amount);

void carsInSouthQueue(GUI *self, int amount);


#endif /* GUI_H_ */