#ifndef __CAN_DRIVER__
#define __CAN_DRIVER__

#include "mcp2515.h"





typedef struct message{
    uint16_t ID;
    uint8_t length;
    uint8_t data[8];
}message;

void can_init();

void can_write(message msg);


int can_transmit_complete();

message can_read();


#endif