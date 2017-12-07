/*! @file
 * General header file, define global common variables.
 * Include useful functions. 
 */
#ifndef GENERAL_HEADER_H_
#define GENERAL_HEADER_H_

#define TRUE 1
#define FALSE 0
#define F_CPU 4915200 //Clock frequency in Hz.
#define BAUD 9600

#define set_bit(reg,bit) (reg |= (1 << bit))
#define clear_bit(reg,bit) (reg &= ~(1 << bit))

#define X_DIR 0
#define Y_DIR 1
#define LEFT_DIR 0
#define RIGHT_DIR 1
#define JOYSTICK_TYPE 0
#define SLIDER_TYPE 1
#define SLIDER_LEFT 2
#define SLIDER_RIGHT 3

#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdbool.h>

#endif /* GENERAL_HEADER_H_ */