/*
 * solenoid.c
 *
 * Created: 20.11.2017 19:41:56
 *  Author: carlmk
 */ 
#include "general_header_node2.h"
#include "solenoid.h"

void solenoid_init(void)
{
	set_bit(DDRE,PE3);
	clear_bit(PORTE,PE3);
}
void solenoid_on(void)
{
	set_bit(PORTE,PE3);
}
void solenoid_off(void)
{
	clear_bit(PORTE,PE3);	
}

void solenoid_pulse(void)
{
	if (SOLENOID_PULSE > SOLENOID_MAX_PULSE )
	{
		return;
	}
	set_bit(PORTE,PE3);
	_delay_ms(SOLENOID_PULSE);
	clear_bit(PORTE,PE3);
}