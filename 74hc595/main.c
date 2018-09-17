/*
* 74hc595.c
*
* Created: 2018-09-17 오후 3:13:45
* Author : 6층교수실PC
* ATmega128 based Programming.
*/
#define F_CPU	16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "ShiftRegister.h"


int main(void)
{
	ShiftRegisterInit();
	
	while (1)
	{
		for (int i=0; i<8; i++)
		{
			ShiftRegisterDataWrite(1<<i);   // LEDs are shifted per 0.5 sec.
			_delay_ms(500);
		}
	}
}
