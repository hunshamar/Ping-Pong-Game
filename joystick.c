#include "adc_driver.h"
#include "joystick.h"



coord_sample joy_init(){
    coord_sample offset;
    offset.x = read_channel(CHANNEL_1);
    offset.y = read_channel(CHANNEL_2);
    return offset;
}
int get_joy_coords_x(coord_sample offset){
    int x_coord = ((double)(read_channel(CHANNEL_1) -offset.x)*100.0/127)*1.04;
    if (x_coord < -100)
        x_coord = -100;
    if (x_coord > 100)
        x_coord = 100;
    return x_coord;
}

int get_joy_coords_y(coord_sample offset){
    int y_coord = ((double)(read_channel(CHANNEL_2) -offset.y)*100.0/127)*1.02;
    if (y_coord < -100)
        y_coord = -100;
    if (y_coord > 100)
        y_coord = 100;
    return y_coord;
}

direction get_direction(int x, int y){
    direction where;
    if (x <= 10 && x >= -10){
        where.x = NEUTRAL;
    }
    else if(x > 0){
        where.x = RIGHT;
    }
    else if(x > 0 ){
        where.x = LEFT;
    }

    if(y <= 10 && y >= -10){
        where.y = NEUTRAL;
    }  
    else if(y > 0){
        where.y = RIGHT;
    }
    else if(y > 0 ){
        where.y = LEFT;
    }
    return where;
}