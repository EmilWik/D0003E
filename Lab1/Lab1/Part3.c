#include <avr/io.h>
#include <stdbool.h>


void button(void){
	
	/*
	Define pull-ups and set outputs high
	Define directions for port pins
	*/
	PORTB += (1<<PB7);
	DDRB = (1<<DDB3)|(1<<DDB2)|(1<<DDB1)|(1<<DDB0);
	
	//Insert nop for synchronization
	asm("nop");


	
	bool risingEdge = false;
	bool currentVar = false;
	
	//LCDDR1 = (1 << currentVar);
	while (1){
		
		if((PINB && (1 << PINB7))){
			risingEdge = true;
			
		}
		else{
			
			if(risingEdge){
				risingEdge = false;
				currentVar = !currentVar;
				LCDDR1 = (1 << currentVar);
			}
		}
	}
	
}