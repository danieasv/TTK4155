/*! @file
 * Joystick driver header file.
 */

#ifndef JOYSTICK_DRIVER_H_
#define JOYSTICK_DRIVER_H_


typedef struct joystick_calibration_data_t {
	int low_x_val;
	int low_y_val;
	int high_x_val;
	int high_y_val;
	int zero_x_val;
	int zero_y_val;
};

//Sets calibration paramters for slider and joystick  & saves them in calibration_data pointer (based on user input)
void calibrate_joystick(struct joystick_calibration_data_t *cal_data);

void calibrate_joystick_state(struct joystick_calibration_data_t *cal_data);

int joystick_read(struct joystick_calibration_data_t *cal_data, int dir);


#endif /* JOYSTICK_DRIVER_H_ */