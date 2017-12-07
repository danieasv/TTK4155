/*! @file
 * Led driver. For testing purpose. 
 */
#include "general_header.h"
#include "led_driver.h"

/*! \fn void led_init(void)
	\brief Initialize led.
*/
void led_init(void){
	set_bit(DDRC,PC0);
	//set_bit(PORTC,PC0);
}

/*! \fn void test_led(void){
	\brief Blink led.
*/
void test_led(void){
	set_bit(PORTC,PC0);
	_delay_ms(500);
	clear_bit(PORTC,PC0);
	_delay_ms(500);
}

/*! \fn void led_on(void)
	\brief Turn led on.
*/
void led_on(void){
	set_bit(PORTC,PC0);
}

/*! \fn void led_toggle(void)
	\brief Toggle led.
*/
void led_toggle(void){
	PORTC ^= (1 << PC0);
}

/*! \fn void led_off(void)
	\brief Turn led off.
*/
void led_off(void){
	clear_bit(PORTC,PC0);
}