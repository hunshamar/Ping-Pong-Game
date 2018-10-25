
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
    _delay_ms(20);
    printf("RtS føasdr: %d \n\r", mcp2515_check_bit(MCP_TXB0CTRL,3));

    printf("Er vi i loopback mode? %02x \n\r\n\r", mcp2515_read(MCP_CANSTAT));



    msg.ID = 23;
    msg.length = 5;


    uint8_t mess[3] = "caa"; 
    for (int i = 0; i < msg.length; i++){
        msg.data[i] = mess[i];
    }
    printf("BEGYNNER PÅ NYTT %d\n\n\n", msg.length);


    
    while(1){
        
    can_write(msg);
    _delay_ms(20);
    
    printf("---------\n\rSendt: \n\r length: %d \n\r data %d \n\r ID %d \n\r \n\r", msg.length, msg.data[0], msg.ID);
    printf("RtS før: %d \n\r", mcp2515_check_bit(MCP_TXB0CTRL,3));

    uint8_t errorR = mcp2515_read(MCP_CANINTF);
    printf("Transmit complete: %d \n\r", mcp2515_check_bit(MCP_CANINTF,0));
    printf("Error register: %02x \n\r", errorR);
    printf("RtS etter: %d \n\r", mcp2515_check_bit(MCP_TXB0CTRL,3));
    printf("Message error: %02x \n\r", mcp2515_read(MCP_TXB0CTRL));

    printf("ARbitration error: %02x \n\r", mcp2515_check_bit(MCP_TXB0CTRL,5));
    _delay_ms(50);

    message recieved = can_read();

    printf("Recieved: \n\r length: %d \n\r data %d \n\r ID %d \n\r-------\n\r\n\r\n\r\n\r", recieved.length, recieved.data[0], recieved.ID);
    



    _delay_ms(2000);


    }
    
    return 0;
}