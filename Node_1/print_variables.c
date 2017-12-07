
#include "general_header.h"
#include "ADC_driver.h"
#include "button_driver.h"
#include "joystick_driver.h"
#include "slider_driver.h"
#include "print_variables.h"

void print_slider_variables(struct slider_calibration_data_t *cal_data){
	
	char* left = " LEFT";
	char* right = " RIGHT";
	char* slider = "SLIDER";
	char* end_line = ": %i  ";

	printf("\r\t\t\t\t\t\t");
	printf(left);
	printf(slider);
	printf(end_line, slider_read(cal_data, LEFT_DIR));

	printf("\r\t\t\t\t\t\t\t\t\t");
	printf(right);
	printf(slider);
	printf(end_line, slider_read(cal_data, RIGHT_DIR));
};

void print_joystick_variables(struct joystick_calibration_data_t *cal_data){
	
	char* joystick = " JOYSTICK";
	char* x_dir = " X";
	char* y_dir = " Y";
	char* end_line = ": %i  ";
	
	printf("\r");
	printf(joystick);
	printf(x_dir);
	printf(end_line, joystick_read(cal_data, X_DIR));
	
	printf("\r\t\t\t");
	printf(joystick);
	printf(y_dir);
	printf(end_line, joystick_read(cal_data, Y_DIR));
};

void print_slider_calibration(struct slider_calibration_data_t *cal_data){
	char* slider = " SLIDER";
	char* left = " LEFT ";
	char* right = " RIGHT";
	char* min = " MIN";
	char* zero = " ZERO";
	char* max = " MAX";
	char* end_line = ": %i  ";

	printf("\n\r");
	printf(left);
	printf(slider);
	printf(min);
	printf(end_line,cal_data->low_l_slider);
	
	printf("\r\t\t\t");
	printf(left);
	printf(slider);
	printf(max);
	printf(end_line,cal_data->high_l_slider);
	
	printf("\n");
	
	printf("\r");
	printf(right);
	printf(slider);
	printf(min);
	printf(end_line,cal_data->low_r_slider);
	
	printf("\r\t\t\t");
	printf(right);
	printf(slider);
	printf(max);
	printf(end_line,cal_data->high_r_slider);
	
	printf("\n");
};

void print_joystick_calibration(struct joystick_calibration_data_t *cal_data){
	
	char* joystick = " JOYSTICK";
	char* x_dir = " X";
	char* y_dir = " Y";
	char* min = " MIN";
	char* zero = " ZERO";
	char* max = " MAX";
	char* end_line = ": %i  ";
	
	printf("\n\r");
	printf(joystick);
	printf(x_dir);
	printf(min);
	printf(end_line, cal_data->low_x_val);
	
	printf("\r\t\t\t");
	printf(joystick);
	printf(x_dir);
	printf(zero);
	printf(end_line, cal_data->zero_x_val);
	
	printf("\r\t\t\t\t\t\t");
	printf(joystick);
	printf(x_dir);
	printf(max);
	printf(end_line, cal_data->high_x_val);
	
	printf("\n");
	
	printf("\r");
	printf(joystick);
	printf(y_dir);
	printf(min);
	printf(end_line,cal_data->low_y_val);
	
	printf("\r\t\t\t");
	printf(joystick);
	printf(y_dir);
	printf(zero);
	printf(end_line, cal_data->zero_y_val);
	
	printf("\r\t\t\t\t\t\t");
	printf(joystick);
	printf(y_dir);
	printf(max);
	printf(end_line, cal_data->high_y_val);
	
	printf("\n");
};