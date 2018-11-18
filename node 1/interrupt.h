#include <avr/interrupt.h>
#include <avr/interrupt.h>
#include "avr/io.h"
#include "can_driver.h"
#include <util/delay.h>
#include "joystick.h"
#include "adc_driver.h"

void interrupt_init();
ISR(TIMER3_OVF_vect);

void interrupt_timer_reset();

int interrupt_timer_countdown_ms(int ms);


long int INTERRUPT_TIMER;

int INTERRUPT_TIMER_LIMIT;