
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
//#include "interrupt.h"


/*
From Aurdoino Shield: 
Solenoid - D10
Motor voltage - D11
IR sensor -A2
*/

int main(){




    /* Initializing */
    uart_init(9600);

    printf("HEI \n\r");
    pwm_init();
    spi_init();
    can_init();
    solenoid_init();
    joystick_init();
    adc_init();
    dac_init();
    motor_controller_init();
    
    sei();
   int asd = 1;


   while(asd){
    
    can_update();

    if (GAME_INFO.data[0] == 'R'){ //Checking if the game is started in rookie mode
        printf("asd");
        game_play(MODE_SPEED);
        asd = 0;
        }
    else if(GAME_INFO.data[0] == 'E'){ //Checking if the game is started in Expert mode
        printf("asd");
        game_play(MODE_POSITION);
        asd = 0;
        }
    GAME_INFO.data[0] = 0;
    }

    message nah;
    nah.ID = 2;
    nah.length = 1;
    nah.data[0] = 1;
    
    PIData_t pi;
    PI_Init(250,10,&pi);


    int i = 0;



    return 0;
}