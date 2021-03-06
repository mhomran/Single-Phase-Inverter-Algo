/*
 * PWM.c
 *
 * Created: 10/17/2020 8:32:27 AM
 *  Author: Mohamed_Hassanin
 */ 

#include <avr/io.h>
#include "PWM.h"

void 
PWM_Init(void)
{
	OCR1A = 1000;
	OCR1B = 1000;
}

void
PWM_Deinit(void)
{
	TCCR1A &= ~(1 << COM1A1 | 1 << COM1B1);
}

void 
PWM_Update(void)
{
	static uint8_t counter = 0;
	
	if(!(counter % 2))
		{
			TCCR1A |= 1 << COM1A1;
			TCCR1A &= ~(1 << COM1B1);			
		}
	else
		{
			TCCR1A |= 1 << COM1B1;
			TCCR1A &= ~(1 << COM1A1);
		}
	
	counter++;	
}

void 
PWM_DcUpdate(void)
{
	uint16_t adcRead = ADC;
	OCR1A = (uint16_t)((((uint32_t)2000) * adcRead) >> 10);
	OCR1B = OCR1A;
}