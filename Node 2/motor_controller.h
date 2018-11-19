#include <avr/io.h>
#include "dac_driver.h"
#include "joystick.h"
#include <util/delay.h>

void motor_controller_init();
void motor_controller_signal(int speed);
uint16_t motor_controller_get_encoder_data();