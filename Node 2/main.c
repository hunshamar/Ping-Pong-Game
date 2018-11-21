
#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <stdio.h>
#include <avr/io.h>
#include "Uart_driver.h"
#include <util/delay.h>
#include "spi_driver.h"
#include "can_driver.h"
#include "mcp2515.h"
#include "pwm_driver.h"
#include "adc_driver.h"
#include "TWI_Master.h"
#include "dac_driver.h"
#include "joystick.h"
#include "motor_controller.h"
#include "pi.h"
#include "solenoid.h"
#include "game.h"

/*
From Aurdoino Shield: 
Solenoid - D10
PWM - D11
IR sensor -A2
*/

int main(){

    /* Initializing */
    uart_init(9600);
    pwm_init();
    spi_init();
    can_init();
    solenoid_init();
    adc_init();
    dac_init();
    motor_controller_init();
    joystick_init();
    sei();

   while(1){
    can_update();
    game_init();
    if (GAME_INFO.data[0] == 'R'){ //Checking if the game is started in rookie mode
        game_play(MODE_SPEED);
        }
    else if(GAME_INFO.data[0] == 'E'){ //Checking if the game is started in Expert mode
        game_play(MODE_POSITION);
        }
    GAME_INFO.data[0] = 0; //resets the game_info
    }

    return 0;
}