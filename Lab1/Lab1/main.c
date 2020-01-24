/*
 * Lab1.c
 *
 * Created: 2020-01-22 10:28:33
 * Author : vikemi-8
 */ 

#include <avr/io.h>
#include "Part1.h"
#include "Part2.h"

int main(void)
{
	CLKPR = 0x80;
	CLKPR = 0x00;
	
	initLCD();

	blink();
	

	//primes();

	/*
	writeChar('3', 0);
	writeChar('1', 1);
	writeChar('4', 2);
	writeChar('1', 3);
	writeChar('5', 4);
	writeChar('9', 5);

	
	writeLong(9876543210);
	*/
}



