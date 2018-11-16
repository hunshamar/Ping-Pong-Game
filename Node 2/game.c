
#include "game.h"




void game_play(MODE m)
{   
    PIData_t pi;
    PI_Init(250,10,&pi);
    

    while(1){

        can_update();
        
        int motor_thrust = 0;



        if (m == MODE_POSITION){
            int position = (get_encoder_data()*-1)/87.65;
            motor_thrust = (slider_get_right_pos(),position,&pi);
        }
        else if (m == MODE_SPEED)
        {
            motor_thrust = joystick_get_x(); 

        }

        motor_controller_cont(motor_thrust);
        
        joystick_to_pwm(-1*(slider_get_right_pos() * 2 - 100));
        
        if(joystick_get_button_status())
        {
            printf("Shoot! \n\r");
            solenoid_shoot();
        }
    }
}
