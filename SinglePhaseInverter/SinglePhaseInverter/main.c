/*
 * SinglePhaseInverter.c
 *
 * Created: 10/17/2020 8:14:56 AM
 * Author : Mohamed_Hassanin
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "PWM/PWM.h"
#include "OS/OS.h"
#include "IO/IO.h"
#include "ADC/ADC.h"

int 
main(void)
{
	IO_Init();
	PWM_Init();
	ADC_Init();
	OS_Init();
	
	sei();
	
  while (1) 
		{
			//DO NOTHING
		}
		
	//unreachable
	return 0;
}

ISR(TIMER1_OVF_vect)
{
	static uint8_t counter = 0;
	
	if(!(counter % 10)) IO_Update();
	
	if(!(counter % 10)) PWM_Update();
	
	if(counter >= 8 && !((counter - 8) % 10)) IO_Deinit();
	if(counter >= 8 && !((counter - 8) % 10)) PWM_Deinit();
	if(counter >= 8 && !((counter - 8) % 10)) PWM_DcUpdate();
	
	counter++;
	if(counter == 255) counter = 5;
}

