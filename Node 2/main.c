
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


int main(){


    uart_init(9600);

    //uart_transmit(8);
    //uart_recieve();

    printf("HEI \n\r");


    message msg;


    can_init();


    msg.ID = 13;
    msg.length = 3;


    uint8_t mess[3] = "aaa"; 
    for (int i = 0; i < msg.length; i++){
        msg.data[i] = mess[i];
    }
    printf("BEGYNNER PÅ NYTT %d\n\n\n", msg.length);


    
    while(1){
        
    can_write(msg);

    printf("---------\n\rSendt: \n\r length: %d \n\r data %d \n\r ID %d \n\r \n\r", msg.length, msg.data[0], msg.ID);
    
    
    message recieved = can_read();
    printf("Recieved: \n\r length: %d \n\r data %d \n\r ID %d \n\r-------\n\r\n\r\n\r\n\r", recieved.length, recieved.data[0], recieved.ID);
    

    _delay_ms(1000);
    }

    return 0;
}