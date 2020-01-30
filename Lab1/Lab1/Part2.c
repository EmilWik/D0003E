#include <avr/io.h>
#include <stdbool.h>

void blink(void){
	
	TCCR1B = (1 << CS12);


	bool state = false;
	unsigned int increment = 0.238422217136 * 0xFFFF; 
	unsigned int nextVal = 0;

	
	while(1){
		
		if (TCNT1 == nextVal)			// if (TCNT1 >= nextVal)
		{
			nextVal = (nextVal + increment) % 0xFFFF;
			
			LCDDR0 = state << 2;
			state = !state;		
		}
		
	}




}