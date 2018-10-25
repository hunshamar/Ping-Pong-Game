
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

int main(){


    uart_init(9600);
    pwm_init();
    

    //uart_transmit(8);
    //uart_recieve();

    printf("HEI \n\r");


    message msg;


    can_init();

    _delay_ms(1000);
    while(1){
    pwm_signal(100);  
    
    _delay_ms(40);
    message recieved = can_read();

    printf("x: %d, y: %d \n\r", recieved.data[0], recieved.data[1]);
    

    
    _delay_ms(40);




    }
    
    return 0;
}