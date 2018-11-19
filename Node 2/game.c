
#include "game.h"

void game_init(){ //Sends the motor over to one side for the posti
   PORTH &= ~(1 << PINH1); //left direction
   send_voltage(70);
   _delay_ms(2000);
   motor_controller_get_encoder_data();
   send_voltage(0);
}

void game_play(MODE m){
    PIData_t pi;
    PI_Init(250,10,&pi);

    message terminate_game;
    terminate_game.ID = 3;
    terminate_game.length = 6;
    terminate_game.data[0] = 1;

    int playing = 1;
    while(playing){
        can_update();
        int motor_thrust = 0;
        if (m == MODE_POSITION){ //Expert mode
            int position = (motor_controller_get_encoder_data()*-1)/87.65;
            if (position > 300) //Ensures valid encoder data
                position = 0;

            if (position > 100 && position < 300)//Ensures valid encoder data
                position = 100;

            motor_thrust = PI_Controller(slider_get_right_pos(),position,&pi);    
        }
        else if (m == MODE_SPEED) //Rookie mode
        {
            motor_thrust = joystick_get_x();
        }
        motor_controller_signal(motor_thrust);

        joystick_to_pwm(-1*(slider_get_right_pos() * 2 - 100)); //updates the right slider
        
        if(joystick_get_button_status()) //Solenoid action
        {
            solenoid_shoot();
        }
        if(adc_read() <= 100){ //Checks if the ball is blocking the IR diode
            printf("Sending teminate message");
            can_write(terminate_game);
            playing =0;
            send_voltage(0); //stops motor
        } 
    } 
} 
