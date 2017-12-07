
/* 
PB5 (OC1A) ON SHIELD
*/

#include "general_header_node2.h"
#include "pwm_driver_node2.h"


void pwm_init(int period_ms){
	//This is PIN 11 on ATMEGA.
	set_bit(DDRB, PB5);// Set data direction output for PIN5 PORTB
	
	//clear_bit(PORTB, PINB5);
	
	//_delay_ms(2000);
	
	// SET WGM1 = 14 to enable TOP = ICR1A, COM1A = 10 to enable non-inverting mode, CS1 = 100(1) for 1/256 prescaler to clk
	TCCR1A = (2 << COM1A0) | (2 << WGM10);
	TCCR1B = (3 << WGM12) | (4 << CS10); 
	
	uint16_t pwm_ticks = 62.5*period_ms;
	// FOR 20ms PERIOD TOP = 1250 = 4E2
	ICR1 = pwm_ticks;

	
	//INITIALIZE WITH NO VOLTAGE ON OUTPUT, COMPARE REGISTER = 0
	OCR1AL = 0x00;
	OCR1AH = 0x00;
	
	// enable compare interrupt
	//TIMSK1 |= (1 << OCIE1A) |(1<<TOIE1);
	
}


ISR (TIMER1_OVF_vect)
{
	
	printf("TIMER 1 OVERFLOW \n\r");
	//set_bit(PORTB, PINB4);
	
}

ISR (TIMER1_COMPA_vect)
{
	printf("TIMER 1A COMPARE INTERRUPT \n\r");
	//clear_bit(PORTB, PINB4);
}

void pwm_set_duty_micro(uint16_t duty_cycle_micro){
	
	if (duty_cycle_micro < 900 || duty_cycle_micro > 2100)
	{
		return;
		
	}
	
	OCR1A = duty_cycle_micro*0.0625;
}