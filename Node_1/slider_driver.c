#include "general_header.h"
#include "button_driver.h"
#include "slider_driver.h"
#include "oled_driver.h"


#ifdef UART_DEBUG
void calibrate_slider(struct slider_calibration_data_t *cal_data) {
	uint8_t this_val = 0;

	char* slider = " SLIDER";
	char* a = "-";
	char* b = " ";
	char* cal_proccess = " CALIBRATION PROSESS: \n";
	char* val_s = "VAL";
	char* x_dir_low = " LEFTMOST";
	char* y_dir_low = " DOWNMOST";
	char* x_dir_high = " RIGHTMOST";
	char* y_dir_high = " UPMOST";
	char* button_s = " BUTTON";
	char* left = " LEFT";
	char* right = " RIGHT";
	char* start_line_1 = "\r MOVE ";
	char* start_line_2 = " TO";
	char* position = " POSISITION\t ";
	char* end_line_1 = " = %i     \t PUSH";
	char* end_line_2 = " TO CONTINUE";

	cal_data->high_l_slider = cal_data->low_l_slider = adc_read(2);
	cal_data->high_r_slider = cal_data->low_r_slider = adc_read(3);

	printf("\n\r");
	printf(slider);
	printf(cal_proccess);

	while (!button_read(slider_l_button)) {
		this_val = adc_read(2);
		printf(start_line_1);
		printf(left);
		printf(slider);
		printf(start_line_2);
		printf(x_dir_low);
		printf(position);
		if (this_val < cal_data->low_l_slider)
		{
			cal_data->low_l_slider = this_val;
		}
		printf(end_line_1, cal_data->low_l_slider);
		printf(left);
		printf(button_s);
		printf(end_line_2);
	}
	while (button_read(slider_l_button)){
		//wait
	}
	_delay_ms(100);
	printf("\n");

	while (!button_read(slider_l_button)) {
		this_val = adc_read(2);
		printf(start_line_1);
		printf(left);
		printf(slider);
		printf(start_line_2);
		printf(x_dir_high);
		printf(position);
		if (this_val > cal_data->high_l_slider)
		{
			cal_data->high_l_slider = this_val;
		}
		printf(end_line_1, cal_data->high_l_slider);
		printf(left);
		printf(button_s);
		printf(end_line_2);
	}
	while (button_read(slider_l_button)){
		//wait
	}
	_delay_ms(100);
	printf("\n");

	while (!button_read(slider_r_button)) {
		this_val = adc_read(3);
		printf(start_line_1);
		printf(right);
		printf(slider);
		printf(start_line_2);
		printf(x_dir_low);
		printf(position);
		if (this_val < cal_data->low_r_slider)
		{
			cal_data->low_r_slider = this_val;
		}
		printf(end_line_1, cal_data->low_r_slider);
		printf(right);
		printf(button_s);
		printf(end_line_2);
	}
	while (button_read(slider_r_button)){
		//wait
	}
	printf("\n");
	_delay_ms(100);

	while (!button_read(slider_r_button)) {
		this_val = adc_read(3);
		printf(start_line_1);
		printf(right);
		printf(slider);
		printf(start_line_2);
		printf(x_dir_high);
		printf(position);
		if (this_val > cal_data->high_r_slider)
		{
			cal_data->high_r_slider = this_val;
		}
		printf(end_line_1, cal_data->high_r_slider);
		printf(right);
		printf(button_s);
		printf(end_line_2);
	}
	while (button_read(slider_r_button)){
		//wait
	}
	_delay_ms(100);
	printf("\n\r");
}
#endif /* UART_DEGUB */

void calibrate_slider_state(struct slider_calibration_data_t *cal_data){
	
	int wait_time_complete_ms = 1500;
	int adc_delay_ms = 250;
	
	oled_reset_screen();

	char* header = "CALIBRATING (1/4)";
	
	uint8_t initial_read_l = adc_read(SLIDER_LEFT);
	uint8_t initial_read_r = adc_read(SLIDER_RIGHT);
	
	if (initial_read_l >= 0 && initial_read_l <= 255)
	{
		cal_data->low_l_slider = cal_data->high_l_slider = initial_read_l;
	}
	
	if (initial_read_r >= 0 && initial_read_r <= 255)
	{
		cal_data->low_r_slider = cal_data->high_r_slider = initial_read_r;
	}
	
	set_cursor(0,13);
	fprintf(FONT5, header); //17 characters long

	set_cursor(2,0);
	fprintf(FONT5, "MOVE LEFT SLIDER TO"); //14 characters long
	
	set_cursor(3,0);
	fprintf(FONT5, "LOWEST POSITION");
	
	set_cursor(4,0);
	fprintf(FONT5, "VALUE: %i", adc_read(SLIDER_LEFT));
	
	set_cursor(6,0);
	fprintf(FONT5, "PRESS LEFT BUTTON TO");
	set_cursor(7,0);
	fprintf(FONT5, "CONTINUE");
	
	oled_update_buffer();
		
	uint8_t this_val = 0;
		
	//Calibrate left slider low
	
	while (!button_read(slider_l_button)){
		_delay_ms(50);
		this_val = adc_read(SLIDER_LEFT);
		
		if (this_val < cal_data->low_l_slider)
		{
			cal_data->low_l_slider = this_val;
		}
		
		set_cursor(4,0);
		fprintf(FONT5, "VALUE: %i  ", cal_data->low_l_slider);
		oled_update_buffer();
	}
	
	while (button_read(slider_l_button));//wait
	
	_delay_ms(adc_delay_ms);
	
	
	//Calibrate left slider high
	
	set_cursor(0,91);
	fprintf(FONT5, "2");
	
	set_cursor(3, 0);
	fprintf(FONT5, "HIGHEST POSITION");
	
	oled_update_buffer();
	
	while (!button_read(slider_l_button)){
		_delay_ms(50);
		this_val = adc_read(SLIDER_LEFT);
		if (this_val > cal_data->high_l_slider)
		{
			if (this_val <= 255){
			cal_data->high_l_slider = this_val;
			}
		}
		
		set_cursor(4,0);
		fprintf(FONT5, "VALUE: %i  ", cal_data->high_l_slider);
		oled_update_buffer();
		
	}
	while (button_read(slider_l_button));//wait
	_delay_ms(100);

	//Set calibration for right slider low

	set_cursor(0,91);
	fprintf(FONT5, "3");

	set_cursor(2,0);
	fprintf(FONT5, "MOVE RIGHT SLIDER TO");
	
	set_cursor(3,0);
	fprintf(FONT5, "LOWEST POSITION ");
	
	set_cursor(6,0);
	fprintf(FONT5, "PRESS RIGHT BUTTON TO");
	
	oled_update_buffer();
	
	while (!button_read(slider_r_button)){
		
		this_val = adc_read(SLIDER_RIGHT);
		
		if (this_val < cal_data->low_r_slider)
		{
			cal_data->low_r_slider = this_val;
		}
		
		set_cursor(4,0);
		fprintf(FONT5, "VALUE: %i  ", cal_data->low_r_slider);
		_delay_ms(50);
		oled_update_buffer();
	}
	
	while (button_read(slider_r_button));//wait
	_delay_ms(100);

	//Set calibration for right slider high

	set_cursor(0,91);
	fprintf(FONT5, "4");

	set_cursor(3,0);
	fprintf(FONT5, "HIGHEST POSITION");
	
	oled_update_buffer();
	
	while (!button_read(slider_r_button)){
		
		this_val = adc_read(SLIDER_RIGHT);
		
		if (this_val > cal_data->high_r_slider)
		{
			if (this_val <= 255){
				cal_data->high_r_slider = this_val;
			}
		}
		
		set_cursor(4,0);
		fprintf(FONT5, "VALUE: %i  ", cal_data->high_r_slider);
		_delay_ms(50);
		oled_update_buffer();
	}
	
	while (button_read(slider_r_button));//wait
	_delay_ms(100);
	
	oled_reset_screen();
	set_cursor(4,4);
	fprintf(FONT5, "CALIBRATION COMPLETE");
	oled_update_buffer();
	
	_delay_ms(wait_time_complete_ms);
	
	oled_reset_screen();
	oled_update_buffer();
}

int slider_read(struct slider_calibration_data_t *cal_data, int dir){
	
	uint8_t measured_val = adc_read(dir+2);
	
	if (dir == 0)
	{
		int corrected_measure = (measured_val - cal_data->low_l_slider);
		int span = (cal_data->high_l_slider - cal_data->low_l_slider);
		float rel_measure = (float)corrected_measure/span;
		return rel_measure*100;
	}
	else if (dir == 1)
	{
		int corrected_measure = (measured_val - cal_data->low_r_slider);
		int span = (cal_data->high_r_slider - cal_data->low_r_slider);
		float rel_measure = (float)corrected_measure/span;
		return rel_measure*100;
	}
	
	return 0;
}