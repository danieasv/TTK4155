
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


int main(void)
{
	uart_init(BAUD);
	_delay_ms(50);
	printf("STARTING UP\n\r");
	
	sei();
	
	SPI_master_init();
	MCP_init();
	CAN_init(MODE_NORMAL);
	pwm_init(20);
	adc_init();
	TWI_Master_Initialise();
	motor_init();
	solenoid_init();
	
	
	//CHECH SYSTEM FUNCTIONS
	servo_set_val(0);
	_delay_ms(500);
	servo_set_val(100);
	_delay_ms(800);
	servo_set_val(50);
	_delay_ms(400);
	solenoid_pulse();
	_delay_ms(100);
	solenoid_pulse();
	//--------------
	
//  	while(1){
// 	 		printf("ADC: %i  \r", adc_read(0));
// 	 		_delay_ms(100);
// 	 	}
	
	while(1){
		play_game(); //receives CAN messages and responds accordingly
		_delay_ms(1000);
	}
	

	
	return 0;
}