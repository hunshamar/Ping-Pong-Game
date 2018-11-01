
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

int main(){


    uart_init(9600);
    pwm_init();
    

    //uart_transmit(8);
    //uart_recieve();

    printf("HEI \n\r");


    message msg;


    can_init();
    adc_init();
    dac_init();
    printf("kommer vi hit?");
    _delay_ms(1000);
    sei();

    int tall = 0;
    while(1){
        printf("før \n\r");
        send_voltage(255);
        printf("Etter \n\r");
        
        
        
        
        
        /*
        if(adc_counter()){
            tall++;
            printf("tall: %d \n\r", tall);
            while(adc_counter()){
            }
            _delay_ms(50);
        }
        else{*/
        
    
    
    
    
    
    
    
    /*
    pwm_signal(100);  
    
    _delay_ms(40);
    message recieved = can_read();

    printf("x: %d, y: %d \n\r", recieved.data[0], recieved.data[1]);
    

    
    _delay_ms(40);


    */

    }
    
    return 0;
}