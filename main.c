/*
 * GccApplication1.c
 *
 * Created: 6/10/2019 12:04:20 AM
 * Author : prouser
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include "I2C_LCD.h"


int main(void)
{
	char buffer[20];
	I2C_LCD_init();
	I2C_LCD_write_string_XY(0, 0, "hello world");
	I2C_LCD_write_string_XY(1, 1, "hello world");
	
	
    /* Replace with your application code */
    while (1) 
    {
    }
}

