/*
 * solenoid.h
 *
 * Created: 20.11.2017 19:42:18
 *  Author: carlmk
 */ 


#ifndef SOLENOID_H_
#define SOLENOID_H_

#define SOLENOID_MAX_PULSE 150
#define SOLENOID_PULSE 100

void solenoid_init(void);
void solenoid_on(void);
void solenoid_off(void);
void solenoid_pulse(void);




#endif /* SOLENOID_H_ */