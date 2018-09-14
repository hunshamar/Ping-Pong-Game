#ifndef __JOYSTICK_H_
#define __JOYSTICK_H_
#include <stdint.h>

typedef enum dir{
    RIGHT,
    LEFT,
    UP,
    DOWN,
    NEUTRAL,
} dir;

typedef struct direction{
    dir x;
    dir y;
} direction;

typedef struct coord_sample {
    int x;
    int y;
}coord_sample;


coord_sample joy_init();

direction get_direction(int x, int y);

int get_joy_coords_x(coord_sample offset);
int get_joy_coords_y(coord_sample offset);
#endif