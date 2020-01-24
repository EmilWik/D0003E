#include <avr/io.h>

void blink(void){

	TCCR1B = (1 << CS12);
	//TCCR1B = (1 << WGM12);
	//TCCR1A = (1 << WGM10) | (1 << WGM11);
	
	
	
	//bool i = false;

	// 1 Hz, probs inte korrekt gjort tho  
	unsigned long l = 0xFFFF/4;
	while(1){
	if ((TCNT1 >= l && TCNT1 < 2*l) || (TCNT1 >= 3*l && TCNT1 < 4*l))
	{
			LCDDR0 = (1 << 2);
	}else{
			LCDDR0 = 0;
	}


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