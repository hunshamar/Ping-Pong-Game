


#include "joystick.h"




void joystick_init(){ //Reads the offset of the joystick
    x_offset = read_adc_channel(CHANNEL_1);
    y_offset = read_adc_channel(CHANNEL_2);

}

int joystick_get_x(){ //reads the X-coordinate from the joystick
    
    int x = ((double)(read_adc_channel(CHANNEL_1)) - x_offset);

    if (x >= 0){ //whats this??
        x /= 0.74;
    }
    else{
        x /= 1.4;
    }
    if (x < 5 && x > -5) //disables the closest positions to origin to remove noise
        x = 0;

    if (x < -100) //saturates input
        x = -100;
    if (x > 100)
        x = 100;

    return x;
}


int joystick_get_y(){ //reads the Y-coordinate from the joystick
    int y = ((double)(read_adc_channel(CHANNEL_2)) - y_offset);

    if (y >= 0){ //whats this
        y /= 0.77;
    }
    else{
        y /= 1.4;
    }
    if (y < 5 && y > -5) //disables the closest positions to origin to remove noise
        y = 0;

    if (y < -100) //saturates input
        y = -100;
    if (y > 100)
        y = 100;

    return y;
}


char* dir_to_string(dir d){
    if (d == 0) return "N";
    if (d == 1) return "R";
    if (d == 2) return "L";
    if (d == 3) return "U";
    if (d == 4) return "D";
    else return "error";
}


int joystick_get_angle(){
    
    int x = joystick_get_x();
    int y = joystick_get_y();

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


dir joystick_get_direction(){ //reads the joystick position and returns the direction


    int x = joystick_get_x();
    int y = joystick_get_y();

    if (x < 80 && x > -80 && y < 80 && y > -80)
        return NEUTRAL;

    int angle = joystick_get_angle(x,y);

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


int slider_get_left_pos(){ //reads finger position on left slider
    return ((double)(read_adc_channel(CHANNEL_3)))*100/255.0;
}

int slider_get_right_pos(){ //reads finger position on right slider
    return ((double)(read_adc_channel(CHANNEL_4)))*100/255.0;
}

int slider_get_left_button_status(){ //reads status of left button
    if (bit_is_set(PINB, PB0))
        return 1;
    else    
        return 0;
}

int slider_get_right_button_status(){ //reads status of right button

    if (bit_is_set(PINB, PB1))
        return 1;
    else    
        return 0;
}

int joystick_get_button_status(){ //reads the status of the joystick button
    if (bit_is_set(PINB, PB2))
        return 0; //active low
    else    
        return 1;
}