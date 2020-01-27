#include <avr/io.h>
#include <stdbool.h>

void blink(void){

	TCCR1B = (1 << CS12);
	//TCCR1B = (1 << WGM12);
	//TCCR1A = (1 << WGM10) | (1 << WGM11);
	

	
	
	//unsigned int l = 0xFFFF/8;
	
	
	// 1 Hz, ser bättre ut. Still osäker tho
	bool state = false;
	unsigned int i = 0;
	unsigned int nextVal = 0;
	while(1){
	
		if (TCNT1 == nextVal)
		{
			nextVal = (++i % 8)*(0xFFFF/8);
			
			LCDDR0 = state << 2;
			state = !state;		
		}
	
		
	
	
	
	
	// 1 Hz, ganska def inte korrekt gjort tho  
			/*
	if ((TCNT1 >= l && TCNT1 < 2*l) || (TCNT1 >= 3*l && TCNT1 < 4*l))
	{
			LCDDR0 = (1 << 2);
	}else{
			LCDDR0 = 0;
	}
*/
	
	
	
/*
		//writeLong(TCNT1);
		if (TCNT1 == 0)
		{
						
			if(i){
				LCDDR0 = (1 << 2);
				i = false;			
			}else{
				LCDDR0 = (1 << 1);
				i = true;
			}
			
		}

*/
	}




}