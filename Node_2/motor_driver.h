
#include "pi.h"

#ifndef MOTOR_DRIVER_H_
#define MOTOR_DRIVER_H_

void motor_init(void);

void motor_set_val(int8_t input_percent);

void reset_encoder();

int16_t read_encoder();

void motor_regulator(struct pi_t *motor_param, int8_t reference);

uint16_t calibrate_encoder();

int16_t read_position(uint16_t encoder_max_val);


int8_t read_position_rel(struct pi_t *motor_param_p);

#endif /* MOTOR_DRIVER_H_ */