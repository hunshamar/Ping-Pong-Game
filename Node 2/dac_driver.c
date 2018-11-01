#include "dac_driver.h"


void dac_init(){
    TWI_Master_Initialise();
    DDRD |= (1<<PD0) | (1<<PD1); //setting SCL and SDA port
}

void send_voltage(uint8_t diff){
    uint8_t message[3];
    message[0] = TWI_ADDRESS;
    message[1] = TWI_COMMAND;
    message[2] = diff;
    
    TWI_Start_Transceiver_With_Data(message,3);
}

