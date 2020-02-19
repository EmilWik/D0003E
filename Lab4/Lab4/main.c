
#include "GUI.h"
#include "TinyTimber.h"

int main(void)
{
	
	initLCD();
	
	GUI gui = initGUI();
	
	INSTALL(&gui, switchFocus, IRQ_PCINT1);
	
	return TINYTIMBER(&gui, test, 0);
	
	
	//printAt(31, 0);
	//printAt(41, 4);
}



