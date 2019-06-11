/*
 * lcdWithInterrupt.c
 *
 * Created: 6/10/2019 12:41:42 PM
 * Author : prouser
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "I2C_LCD.h"
#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

static volatile int i=0;
static volatile char tmp[10]={"nomsg"};

int main(void)
{
	
	I2C_LCD_init();
	_delay_ms(5);
	
	//UBRRH = (unsigned char)(103>>8);
	//UBRRL = (unsigned char)103;
	//UCSRB = (1<<RXEN)|(1<<TXEN)|(1<<RXCIE);
	//UCSRC = (1<<URSEL)|(0<<USBS)|(3<<UCSZ0);
	
	UCSRB = (1 << RXEN) | (1 << TXEN);   // Turn on the transmission and reception circuitry
	UCSRC = (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1); // Use 8-bit character sizes

	UBRRH = (BAUD_PRESCALE >> 8); // Load upper 8-bits of the baud rate value into the high byte of the UBRR register
	UBRRL = BAUD_PRESCALE;
	_delay_ms(5);
	
	
	
	//sei();
	// enable interrupts
	I2C_LCD_write_string_XY(0, 0, tmp);
	
    while (1) 
    {
		while ((UCSRA & (1 << RXC)) == 0) {}; // Do nothing until data have been received and is ready to be read from UDR
			tmp[i] = UDR;	
			i++;
			I2C_LCD_write_string_XY(0, 0, tmp);
    }
}
