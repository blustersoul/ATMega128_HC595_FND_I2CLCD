/*
 * ShiftRegister.c
 * 74HC595
 * Created: 2018-09-17
 * Author: rhoblck@naver.com
 */ 

#include "ShiftRegister.h"

void ShiftRegisterInit(void)
{
	setbit(SHIFT_REGISTER_DDR, SHIFT_REGISTER_LATCH_PIN);
	setbit(SHIFT_REGISTER_DDR, SHIFT_REGISTER_CLOCK_PIN);
	setbit(SHIFT_REGISTER_DDR, SHIFT_REGISTER_DATA_PIN);
}

void ShiftRegisterDataWrite(uint8_t data)
{
	for (int i=7; i<=0; i--)      // ex) data = 0b11000011
	{                             // ex) (0b11000011 >> 7) & 0x01 ===> 0b00000001 & 0b00000001  ====> 0b00000001 ==> 1 : true
		if ( (data>>i) & 0x01 )   // ex) (0b11000011 >> 3) & 0x01 ===> 0b00011000 & 0b00000001  ====> 0b00000000 ==> 0 : false
			setbit(SHIFT_REGISTER_PORT, SHIFT_REGISTER_DATA_PIN);  // data bit high
		else                                                        // data bit low
			clearbit(SHIFT_REGISTER_PORT, SHIFT_REGISTER_DATA_PIN);
		
		//((data>>i) & 0x01) ? setbit(SHIFT_REGISTER_PORT, SHIFT_REGISTER_DATA_PIN) : clearbit(SHIFT_REGISTER_PORT, SHIFT_REGISTER_DATA_PIN);
		ShiftRegisterClock();
	}
	ShiftRegisterLatch();  // latch shift data after shift 8times.
}

void ShiftRegisterClock(void)
{
	setbit(SHIFT_REGISTER_PORT, SHIFT_REGISTER_CLOCK_PIN);
	clearbit(SHIFT_REGISTER_PORT, SHIFT_REGISTER_CLOCK_PIN);
}

void ShiftRegisterLatch(void)
{
	setbit(SHIFT_REGISTER_PORT, SHIFT_REGISTER_LATCH_PIN);
	clearbit(SHIFT_REGISTER_PORT, SHIFT_REGISTER_LATCH_PIN);
}
