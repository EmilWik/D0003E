#include "TinyTimber.h"
#include "GUI.h"
#include "InputHandler.h"
#include "PulseGenerator.h"
#include "PortWriter.h"



GUI				gui			 = initGUI();
PortWriter		portWriter	 = initPortWriter();
PulseGenerator	pGen1		 = initPulseGenerator(&portWriter, &gui, 4);
PulseGenerator	pGen2		 = initPulseGenerator(&portWriter, &gui, 6);
InputHandler	inputHandler = initInputHandler(&gui, &pGen1, &pGen2);


int main(void)
{
	

	INSTALL(&inputHandler, joystickCrossways, IRQ_PCINT1);	// Up, Down & Depressed
	INSTALL(&inputHandler, joystickSideways, IRQ_PCINT0);	// Left & Right
	
	return TINYTIMBER(&inputHandler, initialize, NULL);
}




