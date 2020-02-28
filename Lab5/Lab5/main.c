#include "TinyTimber.h"
#include "Bridge.h"
#include "CarQueue.h"
#include "GUI.h"
#include "InputHandler.h"

#include <avr/io.h>


//#define FOSC 1843200// Clock Speed
#define FOSC 8000000UL
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1



void USART_Init( unsigned int ubrr){
	/* Set baud rate */
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	
	/* Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0);
	
	/* Set frame format: 8data, 1stop bit */
	UCSR0C = (0<<USBS0)|(1<<UCSZ00)|(1<<UCSZ01);
	
}




/*
enum Dirr{
	North = 0,
	South = 1
};
*/

GUI gui = initGUI();
Bridge bridge = initBridge(&gui);
CarQueue northQueue = initCarQueue(&bridge, &gui, 0);
CarQueue southQueue = initCarQueue(&bridge, &gui, 1);
InputHandler inputHandler = initInputHandler(&northQueue, &southQueue, &bridge);










void main( void ){
	
	//initLCD();
	USART_Init(MYUBRR);

	
	
	INSTALL(&inputHandler, test, IRQ_USART0_RX);
	
	sei();
	
	return TINYTIMBER(&gui, initLCD, NULL);
	
	
	
	
	
	
	
	/*
	sei();
	
	USART_Init ( MYUBRR );
	char ReceivedByte; 
	
	initLCD();
	
	 for (;;) // Loop forever
	 {
		 while ((UCSR0A & (1 << RXC0)) == 0) {}; // Do nothing until data have been received and is ready to be read from UDR
		 ReceivedByte = UDR0; // Fetch the received byte value into the variable "ByteReceived"
		 
		 
		 
		 while ((UCSR0A & (1 << UDRE0)) == 0) {}; // Do nothing until UDR is ready for more data to be written to it
		 UDR0 = ReceivedByte; // Echo back the received byte back to the computer
	 }
	*/
	
	/*
	
	initLCD();
	
	USART_Transmit(' ');
	USART_Transmit('e');
	USART_Transmit('n');
	USART_Transmit('d');
	USART_Transmit(' ');
	USART_Transmit('m');
	USART_Transmit('e');

	*/
	

	
	/*
	while(1){
		printAt(&gui, UCSR0C);
	}
	*/
}
	
	

