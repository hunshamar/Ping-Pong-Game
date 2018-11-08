#ifndef _PWM_DRIVER_
#define _PWM_DRIVER_

#include "mcp2515.h"
#include <avr/io.h>

#define PWMMAX 1185
#define PWMMIN 1126

void pwm_init();
int pwm_signal(uint16_t gass);

#endif