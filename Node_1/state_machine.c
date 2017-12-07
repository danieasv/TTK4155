
#include "general_header.h"
#include "oled_driver.h"
#include "joystick_driver.h"
#include "slider_driver.h"
#include "button_driver.h"
#include "state_machine.h"
#include "eeprom.h"
#include "play_game.h"

int menu_item_offset = 20;

int event_handler(struct joystick_calibration_data_t *joystick_cal_data_p, struct slider_calibration_data_t *slider_cal_data_p){
	
	//Set 1024 prescaler for timer
	TCCR1B |= (5 << CS10);
	TIMSK |= (1 << TOIE1);
	
	struct highscore_entry_t highscore_list[5];
	for (int i = 0; i < 5; i++) //INITIALIZE HIGHSCORE LIST
	{
		struct highscore_entry_t entry = {.name = {'T','e','s','t'}, .score = 0};
		highscore_list[i] = entry;
	}
	
	oled_set_last_brightness();
	state_t curr_state = main_menu_state;
	
	while (1)
	{
		
		oled_reset_screen();
		
		switch(curr_state){
			
			case main_menu_state:
			curr_state = main_menu(joystick_cal_data_p);
			break;
			
			case play_game_state:
			curr_state = game_menu(joystick_cal_data_p, slider_cal_data_p, highscore_list);
			break;
			
			case highscore_state:
			curr_state = highscore_menu(joystick_cal_data_p, highscore_list);
			break;
			
			case settings_state:
			curr_state = settings_menu(joystick_cal_data_p);
			break;
			
			case calibrate_state:
			curr_state = calibrate_menu(joystick_cal_data_p);
			break;
			
			case calibrate_j_state:
			calibrate_joystick_state(joystick_cal_data_p);
			curr_state = settings_state;
			break;
			
			case calibrate_s_state:
			calibrate_slider_state(slider_cal_data_p);
			curr_state = settings_state;
			break;
			
			case brightness_state:
			set_brightness_state(joystick_cal_data_p);
			curr_state = settings_state;
			break;

			
			default:
			curr_state = main_menu_state;
			break;
			
		}
	}
	
	
	
	return 0;
}

int settings_menu(struct joystick_calibration_data_t *joystick_cal_data_p){
	
	int number_of_menu_items = 3;
	int first_menu_line = 3;
	
	state_t curr_state = settings_state;
	
	set_cursor(0,0);
	fprintf(FONT8, "SETTINGS");
	
	set_cursor(3,menu_item_offset);
	fprintf(FONT5, "CALIBRATE");
	
	set_cursor(4,menu_item_offset);
	fprintf(FONT5, "BRIGHTNESS");
	
	set_cursor(5,menu_item_offset);
	fprintf(FONT5, "BACK");
	
	int line_selected = first_menu_line;
	set_cursor(line_selected, 0);
	fprintf(FONT5,"-->");
	
	oled_update_buffer();
	
	line_selected = navigate_menu(number_of_menu_items, first_menu_line, line_selected, joystick_cal_data_p);
	
	switch(line_selected){
		
		case 3:
		curr_state = calibrate_state;
		break;
		
		case 4:
		curr_state = brightness_state;
		break;
		
		case 5:
		curr_state = main_menu_state;
		break;
	}
	
	return curr_state;
}

int calibrate_menu(struct joystick_calibration_data_t *joystick_cal_data_p){
	
	int number_of_menu_items = 3;
	int first_menu_line = 3;
	
	state_t curr_state = settings_state;
	
	set_cursor(0,0);
	fprintf(FONT8, "CALIBRATE");
	
	set_cursor(3,menu_item_offset);
	fprintf(FONT5, "JOYSTICK");
	
	set_cursor(4,menu_item_offset);
	fprintf(FONT5, "SLIDER");
	
	set_cursor(5,menu_item_offset);
	fprintf(FONT5, "BACK");
	
	int line_selected = first_menu_line;
	set_cursor(line_selected, 0);
	fprintf(FONT5,"-->");
	
	oled_update_buffer();
	
	line_selected = navigate_menu(number_of_menu_items, first_menu_line, line_selected, joystick_cal_data_p);
	
	switch(line_selected){
		
		case 3:
		curr_state = calibrate_j_state;
		break;
		
		case 4:
		curr_state = calibrate_s_state;
		break;
		
		case 5:
		curr_state = settings_state;
		break;
	}
	
	return curr_state;
}

int main_menu(struct joystick_calibration_data_t *joystick_cal_data_p){
	
	state_t curr_state = main_menu_state;
	
	int number_of_menu_items = 3;
	int first_menu_line = 3;
	
	set_cursor(0,0);
	fprintf(FONT8, "MAIN MENU");
	set_cursor(3,menu_item_offset);
	fprintf(FONT5, "PLAY GAME");
	set_cursor(4,menu_item_offset);
	fprintf(FONT5, "HIGHSCORE");
	set_cursor(5,menu_item_offset);
	fprintf(FONT5, "SETTINGS");
	
	int line_selected = first_menu_line;
	set_cursor(line_selected, 0);
	fprintf(FONT5,"-->");
	
	oled_update_buffer();
	
	line_selected = navigate_menu(number_of_menu_items, first_menu_line, line_selected, joystick_cal_data_p);
	
	switch(line_selected){
		
		case 3:
		curr_state = play_game_state;
		break;
		
		case 4:
		curr_state = highscore_state;
		break;
		
		case 5:
		curr_state = settings_state;
		break;
	}
	
	return curr_state;
}

int game_menu(struct joystick_calibration_data_t *joystick_cal_data_p, struct slider_calibration_data_t *slider_cal_data_p, struct highscore_entry_t *highscore_list_p){
	
	
	int number_of_menu_items = 2;
	int first_menu_line = 3;
	
	state_t curr_state = play_game_state;
	
	set_cursor(0,0);
	fprintf(FONT8, "PLAY PING PONG");
	
	set_cursor(3,menu_item_offset);
	fprintf(FONT5, "NEW GAME");
	
	set_cursor(4,menu_item_offset);
	fprintf(FONT5, "BACK");
	
	int line_selected = first_menu_line;
	set_cursor(line_selected, 0);
	fprintf(FONT5,"-->");
	
	oled_update_buffer();
	
	line_selected = navigate_menu(number_of_menu_items, first_menu_line, line_selected, joystick_cal_data_p);
	
	switch(line_selected){
		
		case 3:
		play_new_game(joystick_cal_data_p, slider_cal_data_p, highscore_list_p);
		break;
		
		case 4:
		curr_state = main_menu_state;
		break;
	}
	
	return curr_state;
}

int navigate_menu(int number_of_menu_items, int first_menu_line, int line_selected, struct joystick_calibration_data_t *joystick_cal_data_p){
	
	int joystick_treshold = 80;
	
	while (button_read(joystick_button))
	{
		if (joystick_read(joystick_cal_data_p, Y_DIR) < -joystick_treshold)
		{
			set_cursor(line_selected, 0);
			fprintf(FONT5,"   ");
			if ((line_selected += 1) >= (first_menu_line+number_of_menu_items))
			{
				line_selected = first_menu_line;
			}
			set_cursor(line_selected, 0);
			fprintf(FONT5,"-->");
			oled_update_buffer();
			while(joystick_read(joystick_cal_data_p, Y_DIR) < -joystick_treshold); //wait
		}
		
		if (joystick_read(joystick_cal_data_p, Y_DIR) > joystick_treshold)
		{
			set_cursor(line_selected, 0);
			fprintf(FONT5,"   ");
			if ((line_selected -= 1) < first_menu_line)
			{
				line_selected = first_menu_line+(number_of_menu_items-1);
			}
			set_cursor(line_selected, 0);
			fprintf(FONT5,"-->");
			oled_update_buffer();
			while(joystick_read(joystick_cal_data_p, Y_DIR) > joystick_treshold); //wait
		}
		
		_delay_ms(50);
	}
	
	while (!button_read(joystick_button)); //wait
	_delay_ms(50);
	
	return line_selected;
}

void set_brightness_state(struct joystick_calibration_data_t *joystick_cal_data_p){
	
	int confirm_val = 0; //USED TO KEEP WHILE LOOP RUNNING
	int new_brightness_val = 0;
	
	int first_menu_line = 4;
	int number_of_menu_items = 4;
	
	while (!confirm_val)
	{
		oled_reset_screen();
		
		_delay_ms(50);
		
		set_cursor(0,22);
		fprintf(FONT5, "SET BRIGHTNESS"); //14 characters
		
		uint8_t brightness_val = EEPROM_read(EEPROM_BRIGHTNESS_ADR);
		int brightness_value_rel = (brightness_val*100)/255;
		set_cursor(2,0);
		fprintf(FONT5, "CURRENT: %i%%", brightness_value_rel);
		
		set_cursor(3,0);
		fprintf(FONT5, "CHOOSE NEW:");
		
		set_cursor(4,menu_item_offset);
		fprintf(FONT5, " 25%%");
		
		set_cursor(5,menu_item_offset);
		fprintf(FONT5, " 50%%");
		
		set_cursor(6,menu_item_offset);
		fprintf(FONT5, " 75%%");
		
		set_cursor(7,menu_item_offset);
		fprintf(FONT5, "100%%");
		
		int line_selected = first_menu_line;
		set_cursor(line_selected, 0);
		fprintf(FONT5,"-->");
		
		oled_update_buffer();
		
		line_selected = navigate_menu(number_of_menu_items, first_menu_line, line_selected, joystick_cal_data_p);
		
		switch (line_selected)
		{
			case 4:
			new_brightness_val = 0.26*255;
			oled_adjust_brightness(new_brightness_val);
			break;
			
			case 5:
			new_brightness_val = 0.51*255;
			oled_adjust_brightness(new_brightness_val);
			break;
			
			case 6:
			new_brightness_val = 0.76*255;
			oled_adjust_brightness(new_brightness_val);
			break;
			
			case 7:
			new_brightness_val = 255;
			oled_adjust_brightness(new_brightness_val);
			break;
		}
		
		
		oled_reset_screen();
		
		line_selected = 3;
		
		set_cursor(2,0);
		fprintf(FONT5, "NEW VALUE: %i%%", (new_brightness_val*100)/255);
		
		set_cursor(3,menu_item_offset);
		fprintf(FONT5, "CONFIRM");
		
		set_cursor(4,menu_item_offset);
		fprintf(FONT5, "BACK");
		
		set_cursor(line_selected, 0);
		fprintf(FONT5,"-->");
		
		oled_update_buffer();
		
		line_selected = navigate_menu(2, 3, 3,joystick_cal_data_p);
		
		if (line_selected == 3)
		{
			confirm_val = 1;
		}
		
	}
	
	EEPROM_write(EEPROM_BRIGHTNESS_ADR, new_brightness_val);
}

int highscore_menu(struct joystick_calibration_data_t *joystick_cal_data_p, struct highscore_entry_t *highscore_list_p){
	
	int number_of_menu_items = 1;
	int first_menu_line = 7;
	
	set_cursor(0,7);
	fprintf(FONT8, "HIGHSCORE LIST");
	
	if (!highscore_list_p[0].score){
		set_cursor(4,48);
		fprintf(FONT5, "EMPTY");
	}
	
	for(int i = 0; i < 5; i++){
		if (highscore_list_p[i].score)
		{
			set_cursor(2+i,10);
			fprintf(FONT5, "%3d points: ", highscore_list_p[i].score);
			for (int j = 0; j < NAME_SIZE; j++)
			{
				fprintf(FONT5, "%c",highscore_list_p[i].name[j]);
			}
		}
	}
	
	oled_update_buffer();
	_delay_ms(200);
	
	while (button_read(joystick_button)){  //Wait for return command
		_delay_ms(100);
	}

	return main_menu_state;
}

int insert_highscore(struct highscore_entry_t *highscore_list_p, uint16_t this_score){
	
	uint16_t old_score;
	int return_val = 0;
	
	for (int i = 0; i < 5; i++)
	{
		if (this_score > highscore_list_p[i].score)
		{
			return_val = 1;
			old_score = highscore_list_p[i].score;
			highscore_list_p[i].score = this_score;
			insert_highscore(highscore_list_p, old_score);
			break;
		}
	}
	return return_val;
}