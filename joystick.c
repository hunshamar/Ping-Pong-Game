


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



int get_angle(double x,double y){

    if (y == 0){
        y = 0.000001;
    }

    int angle = atan(y/x) * 180 / 3.14159265;

    if (x < 0){
        angle += 180;
    }
    if (angle < 0){
        angle += 360;
    }
    return angle;
}


dir get_direction(int x, int y){
    direction where;

    if (x < 3 && x > -3 && y < 3 && y > -3)
        return NEUTRAL;

    int angle = get_angle(x,y);

    if ((angle <= 360 && angle >= 315) || (angle >= 0 && angle <= 45))
        return RIGHT;
    if (angle > 45 && angle < 135)
        return UP;
    if (angle >= 135 && angle <= 225)
        return LEFT;
    if (angle > 225 && angle < 315)
        return DOWN;
    else
        return NEUTRAL;
}

