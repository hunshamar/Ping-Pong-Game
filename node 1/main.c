
#ifndef F_CPU
#define F_CPU 4915200UL
#endif

#include <stdio.h>
#include <avr/io.h>
#include "Uart_driver.h"
#include <util/delay.h>
#include "SRAM.h"
#include "adc_driver.h"
#include "joystick.h"
#include "menu.h"
#include "oled.h"
#include "spi_driver.h"
#include "mcp2515.h"
#include "interrupt.h"

#include "can_driver.h"


int main(){


 
    //Initializing modules
    uart_init(9600);
    SRAM_init();
    joystick_init();
    can_init();
    //interrupt_init();
    //sei();
    oled_init();
    //Declare variables
    
    message msg;
    msg.ID = 1;


    printf("starter node 1");

    
    msg.length = 7;
    //int i = 0;
    
    oled_clear();
    //printf("funker dette? \n\r");

    visual_menu();

    while(1){
        
        printf("Node 1 x: %d , ren x %d , y: %d , ren y %d , direction: %d  \n\r", joystick_get_x(), read_adc_channel(CHANNEL_1), joystick_get_y(), read_adc_channel(CHANNEL_2), joystick_get_direction());
    }

    return 0;
}