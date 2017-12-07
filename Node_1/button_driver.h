/*! @file
 * Implementation of button driver header.
 */
#ifndef BUTTON_DRIVER_H_
#define BUTTON_DRIVER_H_

typedef enum  {
	joystick_button = 0,
	slider_l_button,
	slider_r_button
	} button_t;

uint8_t button_read(button_t button);
int button_init(void);


#endif /* BUTTON_DRIVER_H_ */