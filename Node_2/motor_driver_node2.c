
#include "general_header_node2.h"
#include "motor_driver.h"
#include "TWI_Master.h"
#include "pi.h"

#define ENCODER_OE_PIN 5
#define ENCODER_RST_PIN 6
#define ENCODER_SEL_PIN 3
#define MOTOR_ENABLE_PIN 4
#define DIR_PIN 1


void motor_init(void){
	
	//Motor enabled by setting EN bit, direction with DIR bit
	set_bit(DDRH, MOTOR_ENABLE_PIN);
	set_bit(PORTH, MOTOR_ENABLE_PIN);
	
	//Enable encoder output of MJ1
	set_bit(DDRH, ENCODER_OE_PIN);
	clear_bit(PORTH, ENCODER_OE_PIN);
	
	//Reset encoder
	set_bit(DDRH, ENCODER_RST_PIN);
	clear_bit(PORTH, ENCODER_RST_PIN);
	_delay_us(50);
	set_bit(PORTH, ENCODER_RST_PIN);
	
	//Enable SEL bit
	set_bit(DDRH, ENCODER_SEL_PIN);
	
	//set DIR as output pin
	set_bit(DDRH, DIR_PIN);
	
	//Set encoder bus as input pins
	//DDRK = 0xff;
	
}

int16_t read_encoder(){
	
	// set !OE pin low
	clear_bit(PORTH,ENCODER_OE_PIN);
	
	// set sel low
	clear_bit(PORTH, ENCODER_SEL_PIN);
	_delay_us(20); // wait 20 us.
	
	volatile int16_t data = PINK << 8;
	
	// set SEL high
	set_bit(PORTH, ENCODER_SEL_PIN);
	
	// wait 20 us
	_delay_us(20);
	
	data |= PINK;
	
	_delay_us(10);
	
	// set !OE high
	set_bit(PORTH,ENCODER_OE_PIN);

	//reset_encoder();
	return data;

}


void reset_encoder(){
	clear_bit(PORTH, ENCODER_RST_PIN);
	_delay_us(20);
	set_bit(PORTH, ENCODER_RST_PIN);
}


uint16_t calibrate_encoder(){
	
	//MOVE HEAD TO RIGHTMOST POSITION, RESET THIS ENCODER VALUE TO 0
	
	int8_t MOTOR_CAL_SPEED = 40;
	
	int16_t encoder_val_old = read_encoder();
	
	motor_set_val(-1*MOTOR_CAL_SPEED);
	
	_delay_ms(200);
	
	int16_t encoder_val_new = read_encoder();
	
	printf("BEFORE WHILE: \n\r");
	
	while (encoder_val_new < encoder_val_old){
		encoder_val_old = encoder_val_new;
		_delay_ms(100);
		encoder_val_new = read_encoder();
		
		printf("  INSIDE WHILE 1 \n\r");
	}
	
	motor_set_val(MOTOR_CAL_SPEED);
	_delay_ms(50);
	motor_set_val(0);
	
	reset_encoder();
	printf("     ENCODER RESET\n\r");
	
	_delay_ms(100);
	
	//MOVE HEAD TO LEFTMOST POSITION, STORE VALUE AS MAXIMUM
	
	encoder_val_old = read_encoder();
	
	printf("BEFORE TURNING AROUND \n\r");
	
	motor_set_val(MOTOR_CAL_SPEED);
	
	_delay_ms(200);
	
	encoder_val_new = read_encoder();
	
	while (encoder_val_new > encoder_val_old){
		encoder_val_old = encoder_val_new;
		_delay_ms(100);
		printf("  INSIDE WHILE 2 \n\r");
		encoder_val_new = read_encoder();
	}
	
	motor_set_val(-1*MOTOR_CAL_SPEED);
	_delay_ms(50);
	motor_set_val(0);
	encoder_val_new = read_encoder();
	
	printf("     ENCODER MAXVAL: %i\n\r", encoder_val_new);
	
	return encoder_val_new;
}


int16_t read_position(uint16_t encoder_max_val){
	
	int16_t encoder_val = read_encoder();
	
	int16_t relative_position = encoder_val/encoder_max_val;
	
	int16_t scaled_position = relative_position*1000;
	
	if (scaled_position < 0)
	{
		return 0;
	}
	
	if (scaled_position > 1000)
	{
		return 1000;
	}
		
	return scaled_position;
	
}


void motor_set_val(int8_t input_percent){
	
	if (input_percent < -100 || input_percent > 100)
	{
		return;
	}
	
	uint8_t dac_value;
	
	if (input_percent> 0)
	{
		dac_value = input_percent*2.55;
		set_bit(PORTH, DIR_PIN);
	} 
	else
	{
		dac_value = -1*input_percent*2.55;
		clear_bit(PORTH, DIR_PIN);
	}
	
	//printf("DAC VALUE: %i \n\r", dac_value);
	
	
	int msg_size = 3;
	
	uint8_t dac_adress = 0b01010000;
	uint8_t write_out0_command = 0b00000001; 
	
	uint8_t TWI_msg[3];
	TWI_msg[0] = dac_adress;
	TWI_msg[1] = write_out0_command;
	TWI_msg[2] = dac_value;
	
	
	TWI_Start_Transceiver_With_Data(TWI_msg, msg_size);
	
	//printf("TWI message sent \n\r");
}

void motor_regulator(struct pi_t *motor_param_p, int8_t reference){
	
	int8_t motor_gain = pi_controller(reference, read_position_rel(motor_param_p), motor_param_p);
	
	printf("\t\t\t MOTOR GAIN:   %i  \r", motor_gain);
	
	motor_set_val(motor_gain);
	
}



int8_t read_position_rel(struct pi_t *motor_param_p){
	
	int16_t measurement = read_encoder();
	
	if (measurement < 0)
	{
		measurement = 0;
	}
	else if (measurement > motor_param_p->encoder_max_val)
	{
		measurement = motor_param_p->encoder_max_val;
	}
	
	uint16_t relative_position = ((float)measurement/motor_param_p->encoder_max_val) * 100;
	
	int8_t return_val = (relative_position - 50)*2;
	
	return return_val;
}


/*




void set_position_reference(int16_t pos){
	
	
}


int8_t regulator_gain(int16_t error){
	
	
	//global Sigma += error
	
	return K_p*error + global_sigma*discrete_timestep*K_i //motor gain in percent +/- 100
}

ISR(//Timervector){

	//Fetch virtual reference
	
	//Read encoder val
	
	motor_set_val(//regulator_gain(error))	
	
}



*/