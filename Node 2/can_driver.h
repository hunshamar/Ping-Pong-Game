#ifndef __CAN_DRIVER__
#define __CAN_DRIVER__

#include "mcp2515.h"

#include "Uart_driver.h"
#include <stdio.h>





typedef struct message{
    uint16_t ID;
    
    uint8_t length;
    uint8_t data[8];
}message;

void can_init(); //Kjør før hver recieve

void can_write(message msg);


int can_transmit_complete();

message can_read();

message RECIEVED; //global variabel
message GAME_INFO;

int can_update(); //Updated recieve




#endif