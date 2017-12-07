/*! @file
 * Implementation of adc driver.
 */
#include "general_header.h"
#include "adc_driver.h"


volatile uint8_t adc_conversion_running; //!< Flag to check if conversion is running. 

/*! \fn int adc_init(void) 
	\brief Function to initialize adc. 
*/
int adc_init(void){	 /*!< \todo Need to init ADC before SRAM in main. They should not be dependent */
		cli();
		set_bit(MCUCR,ISC11); //Information about register
		set_bit(GICR,INT1);
		sei();
		return 0;	/*!< \todo  Change to bolean with <stdbool.h>*/
}

/*! \fn uint8_t adc_read(int ch)
	\brief Read adc value.
	\param ch ADC channel.
*/
uint8_t adc_read(int ch){
	adc_conversion_running = 1;
	volatile char *ext_adc = (char *) 0x1400; ///< Start address for the ADC
	
	ext_adc[0] = 0x4+ch;
	
	//sei();
	
	while(adc_conversion_running); ///< Wait for ADC conversion to complete
	
	//cli(); 
	
	return ext_adc[0];
}

/* 	\fn ISR(INT1_vect)
 	\brief Interupt function. Trigged when conversion is complete.
*/ 
ISR(INT1_vect){
	adc_conversion_running = 0;
}