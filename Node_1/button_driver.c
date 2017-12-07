/*! @file
 * Implementation of button driver.
 */

#include "general_header.h"
#include "button_driver.h"

/*! \fn int button_init(void) 
	\brief Initialize button registers.
*/
int button_init(void){
	clear_bit(DDRE,PE2);
	set_bit(DDRB,PB2);
	set_bit(DDRB,PB3);
	return 0;
}
/*! \fn uint8_t button_read(button_t button) 
	\brief Function to read joystick button or touch button push.
	\param button Type of button to read.
*/
uint8_t button_read(button_t button){
	
	switch (button){	
		case joystick_button :
			clear_bit(PORTB,PB2);
			clear_bit(PORTB,PB3);
			_delay_ms(1);
			if (PINE & (1 << PE2)) {
				return 1;
			} 
			else {
				return 0;
			}
		
		case slider_l_button:
			set_bit(PORTB,PB2);
			clear_bit(PORTB,PB3);
			_delay_ms(1);
			if (PINE & (1 << PE2)) {
				return 1;
			}
			else {
				return 0;
			}
		case slider_r_button:
			clear_bit(PORTB,PB2);
			set_bit(PORTB,PB3);
			_delay_ms(1);
			if (PINE & (1 << PE2)) {
				return 1;
			}
			else {
				return 0;
			}
			
		default:
			return -1;
	}
}

