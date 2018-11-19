
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
#include "can_driver.h"




int main(){
    

    /* Initializing modules */
    uart_init(9600);
    SRAM_init();
    joystick_init();
    can_init();
    oled_init();

    /*Runs menu  */

    menu_run();

    return 0;
}