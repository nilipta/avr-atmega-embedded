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

static volatile long counterVal=0;
static volatile char buffer[10]={"0"};
static volatile uint8_t status = 0;

void uart_transmit (unsigned char data);

int main(void)
{
	
	I2C_LCD_init();
	_delay_ms(5);
	/************TIMER****************************/
	//timer interrupt 1 second
	OCR1A = 15624;

	TCCR1B |= (1 << WGM12);
	// Mode 4, CTC on OCR1A

	TIMSK |= (1 << OCIE1A);
	//Set interrupt on compare match

	TCCR1B |= (1 << CS12) | (1 << CS10);
	// set pre-scaler to 1024 and start the timer
	
	/************TIMER END****************************/
	
	/************ SERIEL ****************************/
	
	UCSRB = (1 << RXEN) | (1 << TXEN);   // Turn on the transmission and reception circuitry
	//UCSRB = (1<<RXCIE) | (1 << RXEN) | (1 << TXEN);
	UCSRC = (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1); // Use 8-bit character sizes

	UBRRH = (BAUD_PRESCALE >> 8); // Load upper 8-bits of the baud rate value into the high byte of the UBRR register
	UBRRL = BAUD_PRESCALE;
	_delay_ms(5);
	
	/************ SERIEL END****************************/
	
	
	sei();
	// enable interrupts

	
	
    while (1) 
    {
		I2C_LCD_write_string_XY(0, 0, "sending Number - ");
		_delay_ms(1000);
		//if(counterVal%2==0)
		{
			long tempI=0;
			char tempBuf[10];
			sprintf (buffer, "%lu", counterVal);
			while(buffer[tempI]!='\0'){
				
				//sprintf (tempBuf, "%lu", tempI);
				//I2C_LCD_write_string_XY(0, 0, tempBuf);
				uart_transmit(buffer[tempI]);
				//uart_transmit('X');
				tempI++;	//checking how many digit in counterval
			}
			
			if(buffer[tempI]=='\0')
			{
				
				uart_transmit('\n');
				_delay_ms(400);
				//check for response....
				checkResponseFor5Sec();
			}
			
				
		}	
    }
}


ISR (TIMER1_COMPA_vect)
{
	// action to be done every 1 sec
	counterVal++;
	sprintf (buffer, "%lu", counterVal);
	I2C_LCD_write_string_XY(1, 0, buffer);
}

// function to send data
void uart_transmit (unsigned char data)
{
	while (!( UCSRA & (1<<UDRE)));                // wait while register is free
	UDR = data;                                   // load data in the register
}

void checkResponseFor5Sec()
{
	I2C_LCD_write_string_XY(0, 0,"Response??  ");
	char x[10];
	uint8_t checkInd = 0;
	while(1)
	{
		while (!(UCSRA & (1 << RXC)) )
		{			
		}
		 ; // Do nothing until data have been received and is ready to be read from UDR
		x[checkInd] = UDR;
		checkInd++;
		
		if(x[checkInd] == '|' || x[checkInd] == '\n' || x[checkInd] == '\0')
		{
			for(uint8_t ir =0; ir<10; ir++)
			{
				if(x[ir] == 'o' || x[ir] == 'k' || x[ir] == '|')
					{
						I2C_LCD_write_string_XY(0, 0, " --   ok   --  ");
						break;		
					}
				else
				{
					I2C_LCD_write_string_XY(0, 0, "-- NAN -- ");
					break;
				}
			}
		}
		break;	
		
	}
	
	_delay_ms(1000);
}


/*ISR ( USART_RXC_vect )

{
	char x[5] = "Hello";

	x[1] = UDR ; // Fetch the received byte value into the variable " ByteReceived "

	I2C_LCD_write_string_XY(0, 0, x);
}*/