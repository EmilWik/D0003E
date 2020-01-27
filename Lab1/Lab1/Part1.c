#include <avr/io.h>
#include <stdbool.h>
#include <limits.h>

void initLCD(void){

	CLKPR = 0x80;
	CLKPR = 0x00;

	LCDCRA = (1 << LCDEN) | (1 << LCDAB);
	
	// Vi hade missat LCDPM0-2
	LCDCRB = (1 << LCDMUX0) | (1 << LCDMUX1) | (1 << LCDPM2) | (1 << LCDPM1) | (1 << LCDPM0);
	
	LCDFRR = (1 << LCDCD2) | (1 << LCDCD1) | (1 << LCDCD0);
	
	LCDCCR = (1 << LCDCC3) | (1 << LCDCC2) | (1 << LCDCC1) | (1 << LCDCC0);
}




void writeChar(char c, int pos){	
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




void writeLong(long i){
	long div = i;
	int rest;
	int pos = 5;
	
	if (i == 0){
		writeChar('0', pos--);
	}

	while(pos >= 0){
		rest = div % 10;
		
		if(div == 0){
			writeChar(' ', pos--);
		}
		else{
			div /= 10;
			writeChar(48+rest, pos--);
		}
	}

}




static bool is_prime(long i){
	
	if(i < 2){
		return false;
	}

	for (int n = 2; n < i; n++){
		if ( i % n == 0){
			return false;
		}
	}

	return true;
}


void primes(void){
	
	for (long i = 2; i <= LONG_MAX; i++){
		if (is_prime(i)){
			writeLong(i);
		}
	}
}














/* Behövdes aldrig
void clearLCD(void){
	writeChar(' ', 0);
	writeChar(' ', 1);
	writeChar(' ', 2);
	writeChar(' ', 3);
	writeChar(' ', 4);
	writeChar(' ', 5);
}
*/


