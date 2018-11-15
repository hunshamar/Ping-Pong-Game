#include "solenoid.h"

void solenoid_init(){
    DDRB |= (1<<PB4); //Setter PIN7 som output 
    PORTB |= (1<<PB4); //setter den høy

}

void solenoid_shoot(){
    PORTB &= ~(1<<PB4);
    _delay_ms(1400);
    PORTB |= (1<<PB4);
}