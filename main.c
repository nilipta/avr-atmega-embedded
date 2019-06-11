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


static volatile long  counterVal = 0;

int main(void)
{
	
	I2C_LCD_init();
	
	//timer interrupt 1 second
	OCR1A = 15624;

	TCCR1B |= (1 << WGM12);
	// Mode 4, CTC on OCR1A

	TIMSK |= (1 << OCIE1A);
	//Set interrupt on compare match

	TCCR1B |= (1 << CS12) | (1 << CS10);
	// set prescaler to 1024 and start the timer
	
	
	
	sei();
	// enable interrupts
	
	
    while (1) 
    {
		char buffer[20];
		sprintf (buffer, "%lu", counterVal);
		I2C_LCD_write_string_XY(0, 0, "hello world");
		//_delay_ms(2000);
		I2C_LCD_write_string_XY(1, 0, buffer);
		/* Replace with your application code */
    }
}


ISR (TIMER1_COMPA_vect)
{
	// action to be done every 1 sec
	counterVal++;
}