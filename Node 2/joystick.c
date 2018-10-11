


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

char* dir_to_string(dir d){
    if (d == 0) return "R";
    if (d == 1) return "L";
    if (d == 2) return "U";
    if (d == 3) return "D";
    if (d == 4) return "N";
    else return "error";
}



int get_angle(int x,int y){

    
    if (y == 0){
        double y = 0.000001;
    }

    int angle = atan(((double)(y))/((double)(x))) * 180 / 3.14159265;

    

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

    if (x < 80 && x > -80 && y < 80 && y > -80)
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


int get_left_slider_pos(){
    return ((double)(read_channel(CHANNEL_3)))*100/255.0;
}


int get_right_slider_pos(){    
    return ((double)(read_channel(CHANNEL_4)))*100/255.0;
}

int get_left_button_status(){

    if (bit_is_set(PINB, PB0))
        return 1;
    else    
        return 0;
}

int get_right_button_status(){

    if (bit_is_set(PINB, PB1))
        return 1;
    else    
        return 0;
}

int get_joystick_button_status(){
    if (bit_is_set(PINB, PB2))
        return 0; //active low
    else    
        return 1;
}