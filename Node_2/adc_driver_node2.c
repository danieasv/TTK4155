
#include "general_header_node2.h"
#include "adc_driver_node2.h"


volatile uint8_t adc_conversion_running;

int adc_init(void){	 /*!< \todo Need to init ADC before SRAM in main. They should not be dependent */
	
	cli();
	
	clear_bit(DDRF, PINF0);
	
	//Select ADC0 input channel -> MUX0 = 000000
	ADMUX |= (3<<REFS0); 
	
	//Enable prescaler
	ADCSRA |= (1 << ADPS0 | 1 << ADPS1 | 1 << ADPS2); 
	
	//Enable ADC and interrupt
	ADCSRA |= (1<<ADEN) | (1<<ADIE);
	
	/*
	set_bit(MCUCR,ISC11); //Information about register
	set_bit(GICR,INT1);
	*/ 
	
	sei();
	return 0;	/*!< \todo  Change to bolean with <stdbool.h>*/
}

uint16_t adc_read(int ch){
	adc_conversion_running = 1;
		
	//Clear and set channel
	ADMUX &= (0b11100000);
	ADMUX |= (ch << MUX0);
	
	//Start conversion
	set_bit(ADCSRA, ADSC);
	
	while(adc_conversion_running); //wait
	
	return ADC;
}

ISR(ADC_vect){
	adc_conversion_running = 0;
}