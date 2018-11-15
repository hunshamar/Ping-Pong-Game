#include "solenoid.h"

void solenoid_init(){
    DDRB |= (1<<PB7); //Setter PIN6 som output 

}

void solenoid_shoot(){
    PORTB &= ~(1<<PB7);
    _delay_ms(1400);
    PORTB |= (1<<PB7);
}