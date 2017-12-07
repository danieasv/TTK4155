#include "general_header_node2.h"
#include "uart_driver_node2.h"
#include "spi_driver_node2.h"
#include "mcp_driver_node2.h"
#include "MCP2515.h"
#include "can_driver_node2.h"
#include "pwm_driver_node2.h"
#include "adc_driver_node2.h"
#include "TWI_Master.h"
#include "motor_driver.h"
#include "solenoid.h"
#include "servo_driver.h"
#include "play_game_node2.h"
#include "pi.h"




void play_game(){
	
	//*** initializing game mode

	struct pi_t regulator_param;
	regulator_param.encoder_max_val = calibrate_encoder();
	
	pi_init(K_p, K_i, &regulator_param);	//INITIALIZE REGULATOR WITH PARAMETERS FROM .H GAME FILE
	
	int counter = 0;
	while (counter < 50)
	{
		motor_regulator(&regulator_param, 0);	//POSITION HEAD AT CENTER
		_delay_ms(5);
		counter++;
	}
	solenoid_pulse();
	_delay_ms(100);
	solenoid_pulse();
	
	

	uint16_t ir_data = 0;
	int16_t encoder_val = 0;
	int8_t receive_array[4] = {0,0,0,0};
	int8_t joy_x = 0;
	int8_t joy_y = 0;
	int8_t slider = 0;
	int8_t slider_prev = 0;
	int8_t button = 0;
	
	int game_over = 0;
	
	printf("\n\r ---- NEW GAME STARTED, GOOD LUCK! ---- \n\n\r");
	
	 while(!game_over)
    {

		ir_data = adc_read(0);
		//printf("\n\r ADC data = %i", ir_data);
		
		CAN_receive(receive_array);
		
		joy_x = -1*receive_array[0];
		joy_y = receive_array[1];
		slider = receive_array[2];
		button = receive_array[3];
		
		if (button)
		{
			solenoid_pulse();
			_delay_ms(400);
			
			//_delay_us(10);
		}
		
		motor_regulator(&regulator_param, joy_x);
		
		if (slider > slider_prev + 2 || slider < slider_prev - 2)
		{
			servo_set_val(slider);
			slider_prev = slider;
		}
		
		//printf("IR: \t %i, \t X_JOY \t %i, \t Y_JOY \t %i, \t SLIDER \t %i, \t BUTTON \t %i \t \r", ir_data, joy_x, joy_y, slider, button);
		
		
		
		if (ir_data < THRESHOLD_IR)
		{
			CAN_transfer(0xFF);
			printf("\n\n\r **** GAME ENDED **** \n\n\r");
			game_over = TRUE;
		}
		
		while(ir_data < THRESHOLD_IR){ //wait
			ir_data = adc_read(0);
			_delay_ms(100);
		}
		
    }
	
	
}



