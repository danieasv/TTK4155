

#ifndef STATE_MACHINE_H_
#define STATE_MACHINE_H_

#define NAME_SIZE 4

typedef enum  {
	main_menu_state = 0,
	play_game_state,
	highscore_state,
	settings_state,
	calibrate_state,
	calibrate_j_state,
	calibrate_s_state,
	brightness_state
} state_t;



typedef struct highscore_entry_t {
	
	char name[NAME_SIZE];
	int score;

	} ;


int navigate_menu(int number_of_menu_items, int first_menu_line, int line_selected, struct joystick_calibration_data_t *joystick_cal_data_p);

int main_menu(struct joystick_calibration_data_t *joystick_cal_data);
int event_handler(struct joystick_calibration_data_t *joystick_cal_data_p, struct slider_calibration_data_t *slider_cal_data_p);
int settings_menu(struct joystick_calibration_data_t *joystick_cal_data_p);
int calibrate_menu(struct joystick_calibration_data_t *joystick_cal_data_p);
int game_menu(struct joystick_calibration_data_t *joystick_cal_data_p, struct slider_calibration_data_t *slider_cal_data_p, struct highscore_entry_t *highscore_list_p);

int highscore_menu(struct joystick_calibration_data_t *joystick_cal_data_p, struct highscore_entry_t *highscore_list_p);
int insert_highscore(struct highscore_entry_t *highscore_list_p, uint16_t score); 

void set_brightness_state(struct joystick_calibration_data_t *joystick_cal_data_p);

#endif /* STATE_MACHINE_H_ */