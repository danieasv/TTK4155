
#include "general_header_node2.h"
#include "pwm_driver_node2.h"
#include "servo_driver.h"

void servo_set_val(int slider_val){
	
	if (slider_val < 0 || slider_val > 100)
	{
		return;
	}
	
	uint16_t duty_micro = 900 + (12*slider_val);
	
	pwm_set_duty_micro(duty_micro);
	
}