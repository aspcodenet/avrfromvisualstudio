//https://appelsiini.net/2011/simple-usart-with-avr-libc/

#include <avr/io.h>


#include <stdio.h>
#include "serial.h"

#define F_CPU 16000000UL
#define BAUD 9600
#include <util/setbaud.h>

static FILE uart_stdout = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);

void uart_init(void)
{
	UBRR0H = UBRRH_VALUE;
	UBRR0L = UBRRL_VALUE;

#if USE_2X
	UCSR0A |= _BV(U2X0);
#else
	UCSR0A &= ~(_BV(U2X0));
#endif

	UCSR0C = _BV(UCSZ01) | _BV(UCSZ00); /* 8-bit data */
	UCSR0B = _BV(RXEN0) | _BV(TXEN0);   /* Enable RX and TX */
	stdout = &uart_stdout;
}


int uart_putchar(char chr, FILE* s)
{
	s = s;
	loop_until_bit_is_set(UCSR0A, UDRE0); /* Wait until data register empty. */
	UDR0 = chr;
	return chr;
}

char uart_getchar(void)
{
	loop_until_bit_is_set(UCSR0A, RXC0); /* Wait until data exists. */
	return UDR0;
}
