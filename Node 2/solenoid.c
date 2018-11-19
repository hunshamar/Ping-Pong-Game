#include "solenoid.h"

void solenoid_init(){
    DDRB |= (1<<PB4); //Enables PIN4 as output 
    PORTB |= (1<<PB4); //sets PIN4

}

void solenoid_shoot(){
    PORTB &= ~(1<<PB4); //Shoots solenoide
    _delay_ms(1400);
    PORTB |= (1<<PB4);
}