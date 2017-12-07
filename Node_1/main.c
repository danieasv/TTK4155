
/** @file
This is the main file of Node 1.

*/


#include "general_header.h"
#include <avr/pgmspace.h>

#include "sram_driver.h"
#include "uart_driver.h"
#include "adc_driver.h"
#include "button_driver.h"

#include "joystick_driver.h"
#include "slider_driver.h"
#include "oled_driver.h"
#include "spi_driver.h"
#include "can_driver.h"
#include "mcp_driver.h"
#include "MCP2515.h"
#include "state_machine.h"


int main(void){
	
	#define NORMAL_OPERATION
	//#define UART_DEBUG
	
	uint8_t can_id = 1;
	
	
	// INITIALIZE WITH UART PRINT FUNCTIONS
	#ifdef UART_DEBUG
	//------------- UART INITIALIZATIONS START -------------
	
	char* start_line = "\n\r";
	char* success = " INIT SUCCESS\n";
	char* failed = " INIT FAILED <---\n";
	
	char* uart_s = " UART";
	char* adc_s = " ADC";
	char* sram_s = " SRAM";
	char* buttons_s = " BUTTONS";
	char* oled_s = " OLED";
	char* spi_s = " SPI";
	char* mcp_s = " MCP";
	char* can_s = " CAN";
	
	int uart_init_true = !uart_init(BAUD);
	
	printf("\r\n\n- - - - - - - -\n");
	
	//Initialize uart
	printf(start_line);
	printf(uart_s);
	if (uart_init_true) printf(success);
	else printf(failed);
	
	//Initialize sram
	printf(start_line);
	printf(sram_s);
	if (!SRAM_init())printf(success);
	else printf(failed);
	
	//Initialize adc
	printf(start_line);
	printf(adc_s);
	if (!adc_init())printf(success);
	else printf(failed);
	
	//Initialize buttons
	printf(start_line);
	printf(buttons_s);
	if (!button_init())printf(success);
	else printf(failed);
	
	//Initialize OLED
	printf(start_line);
	printf(oled_s);
	if (!oled_init())printf(success);
	else printf(failed);
	
	//Initialize SPI
	printf(start_line);
	printf(spi_s);
	if (!SPI_master_init())printf(success);
	else printf(failed);

	//Initialize CAN
	if (!CAN_init(MODE_NORMAL, can_id)) {
		printf(start_line);
		printf(can_s);
		printf(success);
	}
	else printf(failed);
	
	//------------- INITIALIZATIONS END -------------

	#endif /* UART_DEGUB */
	
	// INITIALIZE SYSTEM
	#ifdef NORMAL_OPERATION
	
	uart_init(BAUD);
	SRAM_init();
	adc_init();
	button_init();
	oled_init();
	SPI_master_init();
	CAN_init(MODE_NORMAL, can_id);
	
	#endif /* NORMAL_OPERATION */


	struct joystick_calibration_data_t cal_data_joystick = {
		.low_x_val = 0,
		.low_y_val = 0,
		.high_x_val = 255,
		.high_y_val = 255,
		.zero_x_val = 138,
		.zero_y_val = 138,
	};
	
	struct slider_calibration_data_t cal_data_slider = {
		.high_l_slider = 255,
		.high_r_slider = 255,
		.low_l_slider = 0,
		.low_r_slider = 0,
	};
	
	oled_reset_screen();

	//Function for operating Node 1. Contains infinite while-loop.
	event_handler(&cal_data_joystick, &cal_data_slider);

	return 0;

}