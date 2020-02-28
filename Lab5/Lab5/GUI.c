#include <avr/io.h>
#include "TinyTimber.h"

typedef struct {
	Object super;
} GUI;



static void writeChar(char c, int pos){
	int column = pos / 2;						// Determines which pair of digits to write to
	int offset = 4*((pos) % 2);					// Determines which of the 2 digits to write to
	
	#define HEAD  _SFR_MEM8(0xEC + column)		// LCDDR0  - Top of digit
	#define CHEST _SFR_MEM8(0xF1 + column)		// LCDDR5  - Upper middle of digit
	#define LEGS  _SFR_MEM8(0xF6 + column)		// LCDDR10 - Lower middle of digit
	#define FEET  _SFR_MEM8(0xFB + column)		// LCDDR15 - Bottom of digit
	

	// Clears position
	HEAD  &= (0x0F0 >> offset);
	CHEST &= (0x0F0 >> offset);
	LEGS  &= (0x0F0 >> offset);
	FEET  &= (0x0F0 >> offset);
	
	switch (c){
		case '0':
		HEAD  += (1 << (0 + offset));
		CHEST += (1 << (0 + offset)) | (1 << (2 + offset));
		LEGS  += (1 << (0 + offset)) | (1 << (2 + offset));
		FEET  += (1 << (0 + offset));
		break;
		
		case '1':
		CHEST += (1 << (0 + offset));
		LEGS  += (1 << (0 + offset));
		break;
		
		case '2':
		HEAD  += (1 << (0 + offset));
		CHEST += (1 << (0 + offset));
		LEGS  += (1 << (1 + offset)) | (1 << (2 + offset)) | (1 << (3 + offset));
		FEET  += (1 << (0 + offset));
		break;
		
		case '3':
		HEAD  += (1 << (0 + offset));
		CHEST += (1 << (0 + offset));
		LEGS  += (1 << (0 + offset)) | (1 << (1 + offset)) | (1 << (3 + offset));
		FEET  += (1 << (0 + offset));
		break;
		
		case '4':
		CHEST += (1 << (0 + offset)) | (1 << (2 + offset));
		LEGS  += (1 << (0 + offset)) | (1 << (1 + offset)) | (1 << (3 + offset));
		break;
		
		case '5':
		HEAD  += (1 << (0 + offset));
		CHEST += (1 << (2 + offset));
		LEGS  += (1 << (0 + offset)) | (1 << (1 + offset)) | (1 << (3 + offset));
		FEET  += (1 << (0 + offset));
		break;
		
		case '6':
		HEAD  += (1 << (0 + offset));
		CHEST += (1 << (2 + offset));
		LEGS  += (1 << (0 + offset)) | (1 << (1 + offset)) | (1 << (2 + offset)) | (1 << (3 + offset));
		FEET  += (1 << (0 + offset));
		break;
		
		case '7':
		HEAD  += (1 << (0 + offset));
		CHEST += (1 << (0 + offset));
		LEGS  += (1 << (0 + offset));
		break;
		
		case '8':
		HEAD  += (1 << (0 + offset));
		CHEST += (1 << (0 + offset)) | (1 << (2 + offset));
		LEGS  += (1 << (0 + offset)) | (1 << (1 + offset)) | (1 << (2 + offset)) | (1 << (3 + offset));
		FEET  += (1 << (0 + offset));
		break;
		
		case '9':
		HEAD  += (1 << (0 + offset));
		CHEST += (1 << (0 + offset)) | (1 << (2 + offset));
		LEGS  += (1 << (0 + offset)) | (1 << (1 + offset)) | (1 << (3 + offset));
		break;
		
		default:
		break;
	}
}

void printAt(int pos, int num) {
	int pp = pos;
	writeChar( (num % 100) / 10 + '0', pp);
	pp++;
	writeChar( num % 10 + '0', pp);
}



void initLCD(){
	// LCD
	CLKPR = 0x80;
	CLKPR = 0x00;

	LCDCRA = (1 << LCDEN) | (1 << LCDAB);
	LCDCRB = (1 << LCDMUX0) | (1 << LCDMUX1) | (1 << LCDPM2) | (1 << LCDPM1) | (1 << LCDPM0);
	LCDFRR = (1 << LCDCD2) | (1 << LCDCD1) | (1 << LCDCD0);
	LCDCCR = (1 << LCDCC3) | (1 << LCDCC2) | (1 << LCDCC1) | (1 << LCDCC0);
	
	
	
	// Button
	PORTB |= (1<<PB7)|(1<<PB6)|(1<<PB4);
	PORTE |= (1<<PE2)|(1<<PE3);
	DDRB   = (1<<DDB5)|(1<<DDB3)|(1<<DDB2)|(1<<DDB1)|(1<<DDB0);
	//DDRE   = (1<<DDE6)|(1<<DDE4);
	
	//Insert nop for synchronization
	asm("nop");

	PCMSK0 = (1<<PCINT3)|(1<<PCINT2);
	PCMSK1 = (1<<PCINT15)|(1<<PCINT14)|(1<<PCINT12);
	EIMSK = (1 << PCIE1)|(1 << PCIE0);



	// Prints startup chars
//	LCDDR1 = (1 << 2);
//	writeChar('0', 0);
//	writeChar('0', 1);
//	writeChar('0', 4);
//	writeChar('0', 5);
}



void carsOnBridge(GUI *self, int amount){
	printAt(2, amount);
}


void carsInNorthQueue(GUI *self, int amount){
	printAt(0, amount);
}

void carsInSouthQueue(GUI *self, int amount){
	printAt(5, amount);
}



