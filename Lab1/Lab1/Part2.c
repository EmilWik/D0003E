#include <avr/io.h>
#include <stdbool.h>
#include <stdint.h>

void blink(void){

	TCCR1B = (1 << CS11) | (1 << CS10);
	//TCCR1B = (1 << WGM12);
	//TCCR1A = (1 << WGM10) | (1 << WGM11);
	

	
	
	//unsigned int l = 0xFFFF/8;
	
	
	// 1 Hz, ser bättre ut. Still osäker tho
	bool state = false;
	unsigned long i = 0;
	unsigned long nextVal = 0;
	
	unsigned long l = (0xFFFF/2);
	//uint16_t nV = 0;
	
	
	while(1){
	
	
	
		if (TCNT1 == 0)
		{
			//nextVal = (++i % 4)*(0xFFFF/4);
			//nV += l;
			
			LCDDR0 = state << 2;
			state = !state;		
		}
	
		
	
	}




}