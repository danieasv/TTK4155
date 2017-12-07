/*
 * play_game.c
 *
 * Created: 21.11.2017 05:29:11
 *  Author: carlmk
 */ 

#include "play_game.h"
#include "general_header.h"
#include "can_driver.h"
#include "joystick_driver.h"
#include "oled_driver.h"
#include "state_machine.h"
#include "button_driver.h"

// Send Joy_X, Joy_Y, Slider_l, Joy_Button on CAN

uint16_t score;

void play_new_game(struct joystick_calibration_data_t *joy_cal, struct slider_calibration_data_t *slider_cal, struct highscore_entry_t *highscore_list_p){
	
	uint8_t game_over = 0;
	
	// start timer
	TCNT1 = 0;
	
	oled_reset_screen();
	set_cursor(4,15);
	fprintf(FONT8, "PLAYING GAME");
	oled_update_buffer();
	
	int8_t joystick_x = 0;
	int8_t joystick_y = 0;
	uint8_t slider_l = 0;
	uint8_t button_adc = 0;
	uint8_t button = 0;
	int8_t highscore = 0;
	score = 0;

	uint8_t can_id = 0x01; //Assigned random value as Node 2 hasn't enabled filters
	uint8_t can_received_msg = 0;
	
// 	int screen_animation_toggle = 0;
// 	int animation_timer_threshold = 100;

	while(!game_over)
	{
		
// 		if (screen_animation_toggle && (animation_timer > animation_timer_threshold))
// 		{
// 			//animation 1
// 			screen_animation_toggle = 1;
// 			animation_timer = 0;
// 		} 
// 		else if(animation_timer > animation_timer_threshold))
// 		{
// 			//animation 2
// 			screen_animation_toggle = 0;
// 			animation_timer = 0;
// 	
		joystick_x = joystick_read(joy_cal,X_DIR);
		joystick_y = joystick_read(joy_cal,Y_DIR);
		slider_l = slider_read(slider_cal,RIGHT_DIR);
		button_adc = button_read(joystick_button);
		
		if (!button_adc)
		{
			button = 0xFF;
		}
		else {
			button = 0x00;
		}

		int game_input[4] = {joystick_x, joystick_y, slider_l, button};
		CAN_send(can_id,4,game_input);

	
		set_cursor(6,27);
		fprintf(FONT5, "Score: %5d",score + (TCNT1/4800));
		oled_update_buffer();
	
		_delay_us(50);
		
		if (can_received_msg = CAN_check_reveive())
		{
			switch (can_received_msg)
			{
				case 0xFF:
				game_over = TRUE;
				
				oled_reset_screen();
				_delay_ms(50);
				
				score += TCNT1/4800;
				highscore = insert_highscore(highscore_list_p, score); 
				
				if (highscore)
				{
					set_cursor(3,7);
					fprintf(FONT8, "NEW HIGHSCORE!");
					set_cursor(5,15);
					fprintf(FONT8, "%3d points", score);
				}
				else{
					set_cursor(4,27);
					fprintf(FONT8, "GAME OVER");
				}
				
				oled_update_buffer();
				_delay_ms(100);
				while(button_read(joystick_button)); //Wait
				_delay_ms(250);
				
				break;
			}
		}
	}
}

ISR(TIMER1_OVF_vect){
	score += 13;
}