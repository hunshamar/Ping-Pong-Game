#include <avr/io.h>
#include "dac_driver.h"
#include "joystick.h"
#include <util/delay.h>

void motor_controller_init();
void motor_controller_cont(uint8_t magnitude);
uint16_t get_encoder_data();