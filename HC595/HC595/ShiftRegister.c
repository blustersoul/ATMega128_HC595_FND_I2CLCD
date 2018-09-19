﻿/*
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
	clearbit(SHIFT_REGISTER_PORT, SHIFT_REGISTER_LATCH_PIN);
	clearbit(SHIFT_REGISTER_PORT, SHIFT_REGISTER_CLOCK_PIN);
	clearbit(SHIFT_REGISTER_PORT, SHIFT_REGISTER_DATA_PIN);
}

void ShiftRegisterDataWrite(uint8_t data)
{
	for (int i=0; i<8; i++)           // ex) data = 0b11000011
	{                                 // ex) (0b11000011 << 0) & 0x01 ===> 0b11000011 & 0b10000000  ====> 0b10000000 ==> true
 		if ( (data<<i) & 0x80 )       // ex) (0b11000011 << 3) & 0x01 ===> 0b00011000 & 0b10000000  ====> 0b00000000 ==> false
 			setbit(SHIFT_REGISTER_PORT, SHIFT_REGISTER_DATA_PIN);    // data bit high
 		else                                                        
 			clearbit(SHIFT_REGISTER_PORT, SHIFT_REGISTER_DATA_PIN);  // data bit low
		
		//((data<<i) & 0x80) ? setbit(SHIFT_REGISTER_PORT, SHIFT_REGISTER_DATA_PIN) : clearbit(SHIFT_REGISTER_PORT, SHIFT_REGISTER_DATA_PIN);
		ShiftRegisterClock();
	}
	ShiftRegisterLatch();  // latch shift data after shift 8times.
}

void ShiftRegisterClock(void)
{
	clearbit(SHIFT_REGISTER_PORT, SHIFT_REGISTER_CLOCK_PIN);
	setbit(SHIFT_REGISTER_PORT, SHIFT_REGISTER_CLOCK_PIN);
	clearbit(SHIFT_REGISTER_PORT, SHIFT_REGISTER_CLOCK_PIN);
}

void ShiftRegisterLatch(void)
{
	clearbit(SHIFT_REGISTER_PORT, SHIFT_REGISTER_LATCH_PIN);
	setbit(SHIFT_REGISTER_PORT, SHIFT_REGISTER_LATCH_PIN);
	clearbit(SHIFT_REGISTER_PORT, SHIFT_REGISTER_LATCH_PIN);
}
