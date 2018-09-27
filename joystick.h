#ifndef __JOYSTICK_H_
#define __JOYSTICK_H_
#include <stdint.h>
#include<stdio.h>
#include<math.h>
#include<string.h>

#include <avr/io.h>

typedef enum dir{
    NEUTRAL,
    RIGHT,
    LEFT,
    UP, //2
    DOWN, //3
    
} dir;

char* dir_to_string(dir d);

typedef struct direction{
    dir x;
    dir y;
} direction;

typedef struct coord_sample {
    int x;
    int y;
}coord_sample;


coord_sample joy_init();

int get_angle(int x, int y);

dir get_direction(int x, int y);

int get_joy_coords_x(coord_sample offset);
int get_joy_coords_y(coord_sample offset);

int get_left_slider_pos();
int get_right_slider_pos();


int get_left_button_status();
int get_right_button_status();

#endif