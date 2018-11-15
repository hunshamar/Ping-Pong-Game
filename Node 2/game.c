


void game_play_speed(){
    motor_controller_cont(joystick_get_x());
    if(joystick_get_button_status()){
        printf("Shoot! \n\r");
        solenoid_shoot();
    }

    return 0;
}

void game_play_position(){

    motor_controller_cont(PI_Controller((int)(slider_get_right_pos()),position,&pi));
    printf("  Slider right: %d ",slider_get_right_pos());
    printf("    Encoder: %d ",position);
    printf("    Error er: %d \n\r",slider_get_right_pos()-position);
    if(joystick_get_button_status()){
        printf("Shoot! \n\r");
        solenoid_shoot();
    }

    return 0;
}