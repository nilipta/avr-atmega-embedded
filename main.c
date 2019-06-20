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


static volatile long  counterVal = 0;


int main(void)
{
	
	I2C_LCD_init();
	
	//UCSR0B = (1 << RXEN0) | (1 << TXEN0);   // Turn on the transmission and reception circuitry
	//UCSR0C = 0x03; // Use 8-bit character sizes
	
	UCSR0B |= (1<<RXEN0)  | (1<<TXEN0);
	UCSR0C |= (1<<UCSZ00) | (1<<UCSZ01);
	UBRR0H  = (BAUD_PRESCALE >> 8);
	UBRR0L  = BAUD_PRESCALE;
	//UBRR0H = (BAUD_PRESCALE >> 8); // Load upper 8-bits of the baud rate value into the high byte of the UBRR register
	//UBRR0L = BAUD_PRESCALE;
	_delay_ms(5);
	int index = 0;
	char serialBuf[10]=" ";
	char xx;
	
	I2C_LCD_write_string_XY(1, 0, "0");
	do{
		while( ( UCSR0A & ( 1 << RXC0 ) ) == 0 );
		xx = UDR0;
		while (1) 
		{
			I2C_LCD_write_string_XY(0, 0, "Last Value =");
			//I2C_LCD_write_string_XY(1, 0, "hello world");
			// wait until a byte is ready to read
			while( ( UCSR0A & ( 1 << RXC0 ) ) == 0 )
			{
			}
		
			// grab the byte from the serial port
		


			/*while(serialBuf[index] == '\n')
			{
					serialBuf[index] = UDR0;
					index ++;	
			}*/
			//sprintf(serialBuf, "%d",index );
		
		
			char x = UDR0;	
			
				
		
			if(x != '\n')
			{
		
			serialBuf[index] =x;
			index++;	
			
			}
			
			if(x == '\n')
			{
				I2C_LCD_write_string_XY(1, 0, serialBuf);
				index = 0;
				_delay_ms(350);
				sendResponse();
			}
				
		
			/*char resp[3]={'o','k','|'};
			for(uint8_t index = 0;index <3;index++)
			{
				// wait until the port is ready to be written to
				while( ( UCSR0A & ( 1 << UDRE0 ) ) == 0 ){}

				// write the byte to the serial port
				UDR0 = resp[index];
			
			}*/
		
			//sprintf (buffer, "%lu", counterVal);
			//I2C_LCD_write_string_XY(0, 0, "hello world");
			//_delay_ms(2000);
			//I2C_LCD_write_string_XY(1, 0, buffer);
			//_delay_ms(2000);
			//counterVal++;
			/* Replace with your application code */
		}
	}while(xx != '\n');
	
}


void sendResponse()
{
	I2C_LCD_write_string_XY(0, 0, "Response = =");
	_delay_ms(300);
	char resp[4] = "ok|";
	for(uint8_t i = 0; i< 3; i++){
		// wait until the port is ready to be written to
		while( ( UCSR0A & ( 1 << UDRE0 ) ) == 0 ){}

		// write the byte to the serial port
		UDR0 = resp[i];
	}
}


/*

// wait until a byte is ready to read
while( ( UCSR0A & ( 1 << RXC0 ) ) == 0 ){}

// grab the byte from the serial port
recieved_byte = UDR0;

// wait until the port is ready to be written to
while( ( UCSR0A & ( 1 << UDRE0 ) ) == 0 ){}

// write the byte to the serial port
UDR0 = recieved_byte;

*/