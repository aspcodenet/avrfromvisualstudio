#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
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

static volatile uint8_t command[30];
static volatile uint8_t buffer[30];  
static volatile uint8_t buffer_index = 0;

ISR(USART_RX_vect)
{
	if (buffer_index >28)
	{
		buffer_index = 0;
	}
	uint8_t ch = UDR0;
	if (ch == 13)
		return;
	if (ch == 10)
	{
		strcpy((char*)command, (const char*)buffer);
		buffer_index = 0;
		buffer[0] = 0;
		return;
	}
	
	buffer[buffer_index] = ch;
	buffer[buffer_index + 1] = 0;
	buffer_index++;

	/*
	if (ch == '\n')
	{
		strcpy((char*)command, (const char*)buffer);
		buffer_index = 0;
		buffer[0] = 0;
		return;
	}



	buffer[buffer_index] = ch;
	buffer[buffer_index + 1] = 0;
	buffer_index++;*/
}

int blinks = 1;



void HandleCommand(void)
{
	if (strcmp((const char *)command, "ADD") == 0)
	{
		blinks += 1;
	}
	if (strcmp((const char*)command, "DEL") == 0)
	{
		blinks -= 1;
		if (blinks < 1)
			blinks = 1;
	}
}

int main(void)
{
	command[0] = 0;
	uart_init(); 

	DDRD |= (1 << 7);
	while (1)
	{
		if (command[0] != 0)
		{
			printf("COMMAND:%s\n", command);
			HandleCommand();
			command[0] = 0;
		}

		printf("blinks:%d\n", blinks);


		BIT_SET(PORTD, 7);
		for(int i = 0; i < blinks; i++)
			_delay_ms(1000);
		BIT_CLEAR(PORTD, 7);
		for (int i = 0; i < blinks; i++)
			_delay_ms(1000);
	}
	return 0;
}
