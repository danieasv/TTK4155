
#ifndef GENERAL_HEADER_H_
#define GENERAL_HEADER_H_

#define TRUE 1
#define FALSE 0
#define F_CPU 16000000 //Clock frequency in Hz (16 MHz).
#define BAUD 9600

#define set_bit(reg,bit) (reg |= (1 << bit))
#define clear_bit(reg,bit) (reg &= ~(1 << bit))

#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#endif /* GENERAL_HEADER_H_ */