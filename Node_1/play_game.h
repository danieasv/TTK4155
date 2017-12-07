#include "joystick_driver.h"
#include "slider_driver.h"
#include "state_machine.h"

#ifndef PLAY_GAME_H_
#define PLAY_GAME_H_



void play_new_game(struct joystick_calibration_data_t *joy_cal, struct slider_calibration_data_t *slider_cal, struct highscore_entry_t *highscore_list_p);

#endif /* PLAY_GAME_H_ */
