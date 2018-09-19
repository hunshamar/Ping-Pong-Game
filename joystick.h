#ifndef __JOYSTICK_H_
#define __JOYSTICK_H_
#include <stdint.h>
#include<stdio.h>
#include<math.h>
#include<string.h>


typedef enum dir{
    RIGHT,
    LEFT,
    UP,
    DOWN,
    NEUTRAL,
} dir;

char* dir_to_string(dir d){
    if (d == 0) return "R";
    if (d == 1) return "L";
    if (d == 2) return "U";
    if (d == 3) return "D";
    if (d == 4) return "N";
    else return "error";
}

typedef struct direction{
    dir x;
    dir y;
} direction;

typedef struct coord_sample {
    int x;
    int y;
}coord_sample;


coord_sample joy_init();

int get_angle(double x, double y);

dir get_direction(int x, int y);

int get_joy_coords_x(coord_sample offset);
int get_joy_coords_y(coord_sample offset);
#endif