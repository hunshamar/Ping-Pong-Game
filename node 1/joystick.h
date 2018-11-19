#ifndef __JOYSTICK_H_
#define __JOYSTICK_H_
#include <stdint.h>
#include<stdio.h>
#include<math.h>
#include<string.h>
#include "adc_driver.h"

#include <avr/io.h>

typedef enum dir{
    NEUTRAL,
    RIGHT,
    LEFT,
    UP, 
    DOWN, 
    
} dir;

typedef struct direction{
    dir x;
    dir y;
} direction;


//Global variables that gets set by the init function
volatile int x_offset;
volatile int y_offset;


void joystick_init();

int joystick_get_x();
int joystick_get_y();

int joystick_get_angle();

char* dir_to_string(dir d);
dir joystick_get_direction();

int joystick_get_button_status();

int slider_get_left_pos();
int slider_get_right_pos();

int slider_get_left_button_status();
int slider_get_right_button_status();

#endif