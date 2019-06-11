/*
 * blink.c
 *
 * Created: 6/9/2019 8:30:24 PM
 * Author : prouser
 */ 

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
    /* Replace with your application code */
	DDRD = 0XFF;
    while (1) 
    {
		PORTD = 0XFF;
		_delay_ms(1000);
		PORTD = 0X00;
		_delay_ms(1000);
    }
}

