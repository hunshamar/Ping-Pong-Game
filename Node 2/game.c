
#include "game.h"




void game_play(MODE m)
{   
    PIData_t pi;
    PI_Init(250,10,&pi);
    
    message terminate_game;
    terminate_game.ID = 3;
    terminate_game.length = 6;
    terminate_game.data[0] = 1;

    int playing = 1;
    while(playing){
        printf("WHILE LØKKE ER \n\r");
        
        /*
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
        }*/
        if(adc_read() <= 100){
            printf("Sending ");
            can_write(terminate_game);
            playing =0;
        } 
    } 
} 

void game_hardware_test(int time){

    int j = -100;

    int t = 0;
    while(t < time){
        PORTH &= ~(1 << PINH1); //left direction
        send_voltage(100);
        _delay_ms(10000);
        PORTH |= (1 << PINH1); //left direction
        send_voltage(100);
        _delay_ms(10000);
        solenoid_shoot();

        j += 50;
        t += 1;
        if (j > 90)
            j = -100;
        joystick_to_pwm(j);

    }
    send_voltage(0);


}