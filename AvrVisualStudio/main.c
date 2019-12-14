#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "serial.h"


#define BIT_SET(a, b) ((a) |= (1ULL << (b)))

#define BIT_CLEAR(a,b) ((a) &= ~(1ULL<<(b)))

#define BIT_FLIP(a,b) ((a) ^= (1ULL<<(b)))

#define BIT_CHECK(a,b) (!!((a) & (1ULL<<(b)))) 


//Blinka #13 = interna lampan på Uno
//Dvs pin 5 på port B
//https://www.arduino.cc/en/Reference/PortManipulation
//
//void internalLed()
//{
//	DDRB |= (1 << 5);
//	while (1)
//	{
//		BIT_SET(PORTB, 5);
//		_delay_ms(1000);
//		BIT_CLEAR(PORTB, 5);
//		_delay_ms(1000);
//		printf("Hello\n");
//
//	}
//
//}

//Blinka pin 7 (PORT D)
int main(void)
{
	uart_init(); //Redirect stdout!!!

	DDRD |= (1 << 7);
	while (1)
	{
		BIT_SET(PORTD, 7);
		_delay_ms(1000);
		BIT_CLEAR(PORTD, 7);
		_delay_ms(1000);
		printf("Hello\n");

	}
	return 0;
}
