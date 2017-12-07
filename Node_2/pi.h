#ifndef PI_H
#define PI_H

#define SCALING_FACTOR 30
#define K_p 12			 //15
#define K_i 1					//1 

typedef struct pi_t {
	uint16_t Kp;
	uint16_t Ki;	
	int16_t error_sum;
	uint16_t encoder_max_val;
	}; 

void pi_init(int16_t Kp_set, int16_t Ki_set, struct pi_t *regulator_p);
int16_t pi_controller(int16_t set_point, int16_t measurement, struct pi_t* regulator_p);
void pi_reset_integrator(struct pi_t *regulator_p);


#endif /*PI_H */