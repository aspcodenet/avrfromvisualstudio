//https://appelsiini.net/2011/simple-usart-with-avr-libc/

#include <avr/io.h>
#include <avr/interrupt.h>

#include <stdio.h>
#include "serial.h"

//#define F_CPU 8000000UL
#define BAUD 9600
#include <util/setbaud.h>

static FILE uart_stdout = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);
//static FILE uart_stdin = FDEV_SETUP_STREAM(NULL, uart_getchar, _FDEV_SETUP_READ);

#define MYUBBR 10


#define UBRR_VALUE2 (((F_CPU/(BAUD*16UL)))-1)


void uart_init(void)
{
	sei();
	UBRR0H = UBRRH_VALUE;
	UBRR0L = UBRRL_VALUE;

#if USE_2X
	UCSR0A |= _BV(U2X0);
#else
	UCSR0A &= ~(_BV(U2X0));
#endif
//
//
//	UCSR0C = _BV(UCSZ01) | _BV(UCSZ00); /* 8-bit data */
//	UCSR0B = _BV(RXEN0) | _BV(TXEN0);   /* Enable RX and TX */

	//UBRR0H = UBRRH_VALUE;
	//UBRR0L = UBRRL_VALUE;
	UCSR0A &= ~(_BV(U2X0));
	((UCSR0A) |= (1ULL << (RXC0)));
	/*Enable receiver and transmitter and enable interrupt*/
	UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);
	UCSR0C = _BV(UCSZ01) | _BV(UCSZ00); /* 8-bit data */




	stdout = &uart_stdout;
	//	stdin = &uart_stdin;
}


int uart_putchar(char chr, FILE* s)
{
	s = s;
	loop_until_bit_is_set(UCSR0A, UDRE0); /* Wait until data register empty. */
	UDR0 = chr;
	return chr;
}


int uart_charisavailable()
{
	return bit_is_set(UCSR0A, RXC0);
}

char uart_char2()
{
	return UDR0;
}


char uart_getchar(void)
{
	loop_until_bit_is_set(UCSR0A, RXC0); /* Wait until data exists. */
	return UDR0;
}
