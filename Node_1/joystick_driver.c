/*! @file
 * Joystick driver file.
 */
#include "general_header.h"

#include "ADC_driver.h"
#include "button_driver.h"
#include "uart_driver.h"
#include "sram_driver.h"
#include "joystick_driver.h"
#include "oled_driver.h"

#ifdef UART_DEBUG
#include "print_variables.h" 

+/*!
  * \brief Calibrate Joystick
  * @cal_data Pointer to calibration data.
  */
void calibrate_joystick(struct joystick_calibration_data_t *cal_data) {
	uint8_t delay_calibration_ms = 50;
 	int number_of_delay_intervals = 10;
	uint8_t this_val = 0;

	char* joystick = " JOYSTICK";
	char* a = "-";
	char* b = " ";
	char* cal_proccess = " CALIBRATION PROSESS: \n";
	char* x_dir = "X";
	char* y_dir = "Y";
	char* val_s = "VAL";
	char* x_dir_low = " LEFTMOST";
	char* y_dir_low = " DOWNMOST";
	char* x_dir_high = " RIGHTMOST";
	char* y_dir_high = " UPMOST";
	char* button_s = " BUTTON";
	char* start_line_1 = "\r MOVE ";
	char* start_line_2 = " TO";
	char* position = " POSISITION\t ";
	char* end_line_1 = " = %i     \t PUSH";
	char* end_line_2 = " TO CONTINUE";
		
	printf("\n\r");
	printf(joystick);
	printf(cal_proccess);
	
 	cal_data->low_x_val = cal_data->zero_x_val = cal_data->high_x_val = adc_read(X_DIR);	
 	cal_data->low_y_val = cal_data->zero_y_val = cal_data->high_y_val = adc_read(Y_DIR);

	for (int j = 1; j <= number_of_delay_intervals; j++)
	{
		cal_data->zero_x_val = adc_read(X_DIR);
		cal_data->zero_y_val = adc_read(Y_DIR);
			
		printf("\r ! DO NOT TOUCH");
		printf(joystick);
		printf(" ! \t\t X = %i   \t Y = %i   \t|", cal_data->zero_x_val, cal_data->zero_y_val);
			
		for (int k = (number_of_delay_intervals-j); k>0; k--)
		{
			printf(a);
		}
		for (int l = j; l>1; l--)
		{
			printf(b);
		}
		printf("|");
			
		_delay_ms(delay_calibration_ms);
	}
	printf("\n");
	
	//Calibrate X-direction low
	while (button_read(joystick_button)){
		this_val = adc_read(X_DIR);
		if (this_val < cal_data->low_x_val)
		{
			cal_data->low_x_val = this_val;
		}
		printf(start_line_1);
		printf(joystick);
		printf(start_line_2);
		printf(x_dir_low);
		printf(position);
		printf(x_dir);
		printf(end_line_1, cal_data->low_x_val);
		printf(joystick);
		printf(end_line_2);
	}
	while (!button_read(joystick_button));//wait
	_delay_ms(100);
		
	//Calibrate X-direction high
	
	while (button_read(joystick_button)){
		this_val = adc_read(X_DIR);
		if (this_val > cal_data->high_x_val)
		{
			cal_data->high_x_val = this_val;
		}
		printf(start_line_1);
		printf(joystick);
		printf(start_line_2);
		printf(x_dir_high);
		printf(position);
		printf(x_dir);
		printf(end_line_1, cal_data->high_x_val);
		printf(joystick);
		printf(end_line_2);
	}
	while (!button_read(joystick_button));//wait
	_delay_ms(100);

	//Set calibration for Y-direction low
	while (button_read(joystick_button)){
		this_val = adc_read(Y_DIR);
		if (this_val < cal_data->low_y_val)
		{
			cal_data->low_y_val = this_val;
		}
		printf(start_line_1);
		printf(joystick);
		printf(start_line_2);
		printf(y_dir_low);
		printf(position);
		printf(y_dir);
		printf(end_line_1, cal_data->low_y_val);
		printf(joystick);
		printf(end_line_2);
	}
	while (!button_read(joystick_button));//wait
	_delay_ms(100);

	//Calibrate Y direction high
	
	while (button_read(joystick_button)){
		this_val = adc_read(Y_DIR);
		if (this_val > cal_data->high_y_val)
		{
			cal_data->high_y_val = this_val;
		}
		printf(start_line_1);
		printf(joystick);
		printf(start_line_2);
		printf(y_dir_high);
		printf(position);
		printf(y_dir);
		printf(end_line_1, cal_data->high_y_val);
		printf(joystick);
		printf(end_line_2);
	}
	while (!button_read(joystick_button));//wait
	_delay_ms(100);
	
	printf("\n");
}
#endif /* UART_DEGUB */


void calibrate_joystick_state(struct joystick_calibration_data_t *cal_data) {
	
	oled_reset_screen();
	
	uint8_t delay_calibration_ms = 500;
	int number_of_delay_intervals = 10;
	uint8_t this_val = 0;

	char* a = "-";
	char* b = " ";
	char* dont_touch = "DO NOT TOUCH JOYSTICK";
	char* blanc = "                     ";
	char* header = "CALIBRATING (1/5)";
	
	set_cursor(0,15);
	fprintf(FONT5, header); //20 characters long
	
	
	set_cursor(6,16);
	fprintf(FONT5, "X =      Y =");
	
	set_cursor(4, 28);
	fprintf(FONT5, "|---------|");
	
	for (int i = 0; i<5; i++)
	{
		set_cursor(2,0);
		fprintf(FONT5, blanc);
		oled_update_buffer();
		_delay_ms(delay_calibration_ms);
		set_cursor(2,0);
		fprintf(FONT5, dont_touch);
		oled_update_buffer();
		_delay_ms(delay_calibration_ms);
	}
	
	
	cal_data->low_x_val = cal_data->zero_x_val = cal_data->high_x_val = adc_read(X_DIR);
	cal_data->low_y_val = cal_data->zero_y_val = cal_data->high_y_val = adc_read(Y_DIR);
	

	for (int j = 1; j <= number_of_delay_intervals; j++)
	{
		set_cursor(6, 40);
		fprintf(FONT5, "   ");
		
		set_cursor(6, 94);
		fprintf(FONT5, "   ");
		
		
		cal_data->zero_x_val = adc_read(X_DIR);
		cal_data->zero_y_val = adc_read(Y_DIR);
		
		set_cursor(6, 40);
		fprintf(FONT5, "%i", cal_data->zero_x_val);
		
		set_cursor(6, 94);
		fprintf(FONT5, "%i", cal_data->zero_y_val);
		
		set_cursor(4, 28);
		fprintf(FONT5, "|");
		for (int k = (number_of_delay_intervals-j); k>0; k--)
		{
			fprintf(FONT5, a);
		}
		for (int l = j; l>1; l--)
		{
			fprintf(FONT5, b);
		}
		
		fprintf(FONT5, "|");
		
		oled_update_buffer();
		_delay_ms(delay_calibration_ms);
		
	}

	_delay_ms(delay_calibration_ms);
	
	
	oled_reset_screen();
	set_cursor(0,15);
	fprintf(FONT5, header); //20 characters long
	set_cursor(0,93);
	fprintf(FONT5, "%i", 2);
	set_cursor(2,0);
	fprintf(FONT5, "MOVE JOYSTICK:"); //14 characters long
	set_cursor(6,0);
	fprintf(FONT5, "PRESS JOYSTICK TO");
	set_cursor(7,0);
	fprintf(FONT5, "CONTINUE");
	
	oled_update_buffer();
	
	//Calibrate X-direction low
	set_cursor(2, 90);
	fprintf(FONT5, "LEFT ");
	
	while (button_read(joystick_button)){
		
		this_val = adc_read(X_DIR);
		
		if (this_val < cal_data->low_x_val)
		{
			cal_data->low_x_val = this_val;
		}
		
		set_cursor(4,0);
		fprintf(FONT5, "X = %i  ", cal_data->low_x_val);
		_delay_ms(50);
		oled_update_buffer();
	}
	
	while (!button_read(joystick_button));//wait
	_delay_ms(50);
	
	
	//Calibrate X-direction high
	set_cursor(0,93);
	fprintf(FONT5, "%i", 3);
	set_cursor(2, 90);
	fprintf(FONT5, "RIGHT");
	
	oled_update_buffer();
	
	while (button_read(joystick_button)){
		this_val = adc_read(X_DIR);
		if (this_val > cal_data->high_x_val)
		{
			cal_data->high_x_val = this_val;
		}
		
		set_cursor(4,0);
		fprintf(FONT5, "X = %i  ", cal_data->high_x_val);
		_delay_ms(50);
		oled_update_buffer();
		
	}
	while (!button_read(joystick_button));//wait
	_delay_ms(50);

	//Set calibration for Y-direction low
	set_cursor(0,93);
	fprintf(FONT5, "%i", 4);
	set_cursor(2, 90);
	fprintf(FONT5, "DOWN ");
	
	oled_update_buffer();
	
	while (button_read(joystick_button)){
		this_val = adc_read(Y_DIR);
		if (this_val < cal_data->low_y_val)
		{
			cal_data->low_y_val = this_val;
		}
		
		set_cursor(4,0);
		fprintf(FONT5, "Y = %i  ", cal_data->low_y_val);
		_delay_ms(50);
		oled_update_buffer();

	}
	while (!button_read(joystick_button));//wait
	_delay_ms(50);

	//Calibrate Y direction high
	set_cursor(0,93);
	fprintf(FONT5, "%i", 5);
	set_cursor(2, 90);
	fprintf(FONT5, "UP   ");
	
	oled_update_buffer();
	
	
	while (button_read(joystick_button)){
		this_val = adc_read(Y_DIR);
		if (this_val > cal_data->high_y_val)
		{
			cal_data->high_y_val = this_val;
		}
		set_cursor(4,0);
		fprintf(FONT5, "Y = %i  ", cal_data->high_y_val);
		_delay_ms(50);
		oled_update_buffer();

	}
	while (!button_read(joystick_button));//wait
	_delay_ms(50);
	
	oled_reset_screen();
	set_cursor(4,4);
	fprintf(FONT5, "CALIBRATION COMPLETE");
	oled_update_buffer();
	
	_delay_ms(1500);
	oled_reset_screen();
	oled_update_buffer();
	
}

int joystick_read(struct joystick_calibration_data_t *cal_data, int dir){
	
	uint8_t measured_val = adc_read(dir);
	
	if (dir == X_DIR)
	{
		if (measured_val >= cal_data->zero_x_val)
		{
			int corrected_measure = (measured_val - cal_data->zero_x_val);
			int span = (cal_data->high_x_val - cal_data->zero_x_val);
			float rel_measure = (float)corrected_measure/span;
			return rel_measure*100;
		}
		else if (measured_val < cal_data->zero_x_val) 
		{
			int corrected_measure = (measured_val - cal_data->zero_x_val);
			int span = (cal_data->zero_x_val - cal_data->low_x_val);
			float rel_measure = (float)corrected_measure/span;
			return rel_measure*100; 
		}
	} 
	else if (dir == 1)
	{
		if (measured_val >= cal_data->zero_y_val)
		{
			int corrected_measure = (measured_val - cal_data->zero_y_val);
			int span = (cal_data->high_x_val - cal_data->zero_y_val);
			float rel_measure = (float)corrected_measure/span;
			return rel_measure*100;
		}
		else if (measured_val < cal_data->zero_y_val)
		{
			int corrected_measure = (measured_val - cal_data->zero_y_val);
			int span = (cal_data->zero_y_val - cal_data->low_y_val);
			float rel_measure = (float)corrected_measure/span;
			return rel_measure*100;
		}
	}
	
	return 0;
}

