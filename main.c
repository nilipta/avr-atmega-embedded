/*
 * rtc328.c
 *
 * Created: 6/23/2019 7:23:37 PM
 * Author : prouser
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "I2C_LCD.h"
#include "rtc3231.h"

static volatile long  counterVal = 0;

//char t[]="Time: ";
//char da[]=" Date: ";


rtc_t today;
rtc_t set_date;

void setDate()
{
rtc_t rtc;
rtc.hour = dec2bcd(3); //24 hour
rtc.min =  dec2bcd(8); // minute
rtc.sec =  dec2bcd(10); //second
rtc.date = dec2bcd(24);   //28
rtc.month = dec2bcd(6);  //08
rtc.year = dec2bcd(19);  //2017
rtc.weekDay = 7;         // Friday: 5th day of week considering Monday as first day.
ds3231_SetDateTime(&rtc);
}


int main(void)
{

	I2C_LCD_init();
	_delay_ms(100);
	
	//setDate();
	
	I2C_LCD_write_string_XY(1, 0, "Hello world");
	_delay_ms(1000);
	
	I2C_LCD_clear();
	
	
  while (1) 
    {
	char timeMsg[16]="";
	char dateMsg[16]="";
	ds3231_GetDateTime(&today);
	char d_y[3];
	char d_m[3];
	char d_d[3];
	char d_h[3];
	char d_mi[3];
	char d_s[3];
	char d_tmp[4];
	
	itoa(bcd2dec(today.hour) , d_h, 10); //hour
	itoa(bcd2dec(today.min), d_mi, 10);  //min
	itoa(bcd2dec(today.sec), d_s, 10);   //sec
	itoa(bcd2dec(today.date), d_d, 10);  //day
	itoa(bcd2dec(today.month), d_m, 10); //month
	itoa(bcd2dec(today.year), d_y, 10);  //year
	
	strcat(timeMsg,"Time:");   //hour
	strcat(timeMsg,d_h);   //hour
	strcat(timeMsg,":");

	strcat(timeMsg,d_mi);  //min
	strcat(timeMsg,":");
	
	strcat(timeMsg,d_s);   //sec
	
	strcat(dateMsg,"Date:");   //day
	strcat(dateMsg,d_d);   //day
	strcat(dateMsg,".");
	
	strcat(dateMsg,d_m);   //month
	strcat(dateMsg,".20");
	
	strcat(dateMsg,d_y);   //year


	I2C_LCD_goto_XY(0, 0);
	I2C_LCD_write_string(timeMsg);
	
	I2C_LCD_goto_XY(1, 0);
	I2C_LCD_write_string(dateMsg);
	_delay_ms(1000);
	I2C_LCD_clear();
    }
}

