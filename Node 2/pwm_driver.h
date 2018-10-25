#ifndef _PWM_DRIVER_
#define _PWM_DRIVER_

#include "mcp2515.h"
#include <avr/io.h>

void pwm_init();
void pwm_signal(uint16_t gass);

#endif