
#include "general_header.h"

#ifndef SLIDER_DRIVER_H_
#define SLIDER_DRIVER_H_

typedef struct slider_calibration_data_t {
	uint8_t high_l_slider;
	uint8_t low_l_slider;
	uint8_t high_r_slider;
	uint8_t low_r_slider;
};


void calibrate_slider(struct slider_calibration_data_t *cal_data);
void calibrate_slider_state(struct slider_calibration_data_t *cal_data);

int slider_read(struct slider_calibration_data_t *cal_data, int dir);

#endif /* SLIDER_DRIVER_H_ */