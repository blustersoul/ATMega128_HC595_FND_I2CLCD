/*
*
*
*
*/

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include "I2C_LCD.h"
#include "FND.h"
#include "ShiftRegister.h"

volatile uint8_t timercounter0 = 0;
volatile unsigned int FndValue = 0;

void SetFndValue(int value)
{
	FndValue = value;
}

ISR(TIMER0_OVF_vect)
{
	if(timercounter0%4 == 0){
		displayFND(0, FndValue%10);  // 1???먮━
	}
	else if(timercounter0%4 == 1){
		displayFND(1, FndValue%100/10);  // 10???먮━
	}
	else if(timercounter0%4 == 2){
		displayFND(2, FndValue%1000/100);  // 100???먮━
	}
	else if(timercounter0%4 == 3){
		displayFND(3, FndValue/1000);  // 1000???먮━
	}
	
	timercounter0++;
	
	if (timercounter0 >= 200){
		timercounter0 = 0;
	}
}

int main(void)
{
	unsigned int count=0;
	char buffer[20];
	I2C_LCD_init();
	FND_init();
	sei();
	I2C_LCD_write_string_XY(0, 0, "hello world");
	
	while (1)
	{
		sprintf(buffer, "%05d", count);
		I2C_LCD_write_string_XY(1,0, buffer);
		SetFndValue(count);
		count++;
		_delay_ms(10);
	}
}

