#ifndef _DAC_DRIVER_
#define _DAC_DRIVER_

#include "TWI_Master.h"
#include <stdint.h>
#include <avr/io.h>


void dac_init();

void send_voltage(uint8_t diff);

#define TWI_ADDRESS 0b01010000
#define TWI_COMMAND 0b00000000

#endif