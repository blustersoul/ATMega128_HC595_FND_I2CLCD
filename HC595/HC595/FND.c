/*
* FND.c
*
* Created: 2018-09-14 오후 2:25:49
* Author : rhoblack
* email  : jinho@korcham.net
*
* 인터럽트 방식의 4FND 출력 코드
* timer/counter 0 사용, 64분주 설정
*
*/

#include "FND.h"
#include "ShiftRegister.h"

void FND_init(void)
{
	ShiftRegisterInit();
	IOPortInit();
	TimerInterruptInit();
}

void IOPortInit(void)
{
	FND_DATA_DDR = 0xff;   // FND Data Port
	FND_CONTROL_DDR |= 0xf0;   // FND Control Port
}

void TimerInterruptInit(void)
{
	TCCR0 |= (1<<CS02) | (1<<CS01) | (0<<CS00);
	TIMSK |= (1<<TOIE0);
}

void displayFND(uint8_t position, uint8_t number)
{
	                    // 0   1     2     3     4     5     6     7     8     9
	uint8_t numFont[] =	{0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x27, 0x7f, 0x67};
	          // FND 위치  1000,  100,   10,    1
	uint8_t fndselect[] = {0x80, 0x40, 0x20, 0x10};
	
	FND_CONTROL_PORT = FND_CONTROL_PORT|0xf0;
	FND_CONTROL_PORT &= ~fndselect[position];
	//FND_DATA_PORT = numFont[number];
	ShiftRegisterDataWrite(numFont[number]);
}

void displayNumber(int count)
{
	displayFND(0, count%10);  // 1의 자리
	_delay_ms(1);
	displayFND(1, count%100/10);  // 10의 자리
	_delay_ms(1);
	displayFND(2, count%1000/100);  // 100의 자리
	_delay_ms(1);
	displayFND(3, count/1000);  // 1000의 자리
	_delay_ms(1);
}