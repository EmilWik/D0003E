#include <avr/io.h>
#include <avr/interrupt.h>
#include "TinyTimber.h"
#include "Bridge.h"
#include "CarQueue.h"
#include "GUI.h"
#include "InputHandler.h"
#include "TrafficLight.h"
#include "SimWriter.h"


#define FOSC 8000000UL // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1
	
void USART_Init( unsigned int ubrr);



GUI			 gui		  = initGUI();
Bridge		 bridge		  = initBridge(&gui);
CarQueue	 northQueue	  = initCarQueue(&gui, &bridge, North);
CarQueue	 southQueue	  = initCarQueue(&gui, &bridge, South);
InputHandler inputHandler = initInputHandler(&gui, &bridge, &northQueue, &southQueue);
SimWriter	 simWriter	  = initSimWriter();
TrafficLight trafficLight = initTrafficLight(&simWriter);


int main( void ){
	
	USART_Init(MYUBRR);
	initLCD();

	INSTALL(&inputHandler, readInput, IRQ_USART0_RX);
	
	sei();
	
	return TINYTIMBER(&trafficLight, trafficLightFunc, NULL);
		
}
	


void USART_Init( unsigned int ubrr){
	/* Set baud rate */
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	
	/* Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0);
	
	/* Set frame format: 8data, 1stop bit */
	UCSR0C = (0<<USBS0)|(1<<UCSZ00)|(1<<UCSZ01);
	
}







/*	echo

	char ReceivedByte; 
	for (;;) // Loop forever
	{
		 while ((UCSR0A & (1 << RXC0)) == 0) {}; // Do nothing until data have been received and is ready to be read from UDR
		 ReceivedByte = UDR0; // Fetch the received byte value into the variable "ByteReceived"
		 
		 
		 
		 while ((UCSR0A & (1 << UDRE0)) == 0) {}; // Do nothing until UDR is ready for more data to be written to it
		 UDR0 = ReceivedByte; // Echo back the received byte back to the computer
	}
*/