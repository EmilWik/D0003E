#include <avr/io.h>
#include <stdbool.h>

void blink(void){
	
	TCCR1B = (1 << CS12);


	bool state = false;
	unsigned int i = 0;
	unsigned int nextVal = 0;

	
	while(1){
		
		if (TCNT1 == nextVal)			// if (TCNT1 >= nextVal)
		{
			nextVal = (++i % 4)*(0xFFFF/4);
			
			LCDDR0 = state << 2;
			state = !state;		
		}
	
		
	
	}




}