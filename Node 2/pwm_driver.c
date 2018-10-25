#include "pwm_driver.h"

void pwm_init(){
    DDRB |= (1<<PINB5); // Setter PB5 som output
    TCCR1A |= (1 << WGM11);
    //TCCR1A &= (0 << WGM10);
    TCCR1B |=  (1 << WGM12) | (1 << WGM13); //Setter til mode 14, fast PWM. Se side 145 på atmega 2560!

    TCCR1A |= (1 << COM1A1); 
    TCCR1A |= (1 << COM1A0); // Setter til compare output mode, slik at OC1A er comperator mot timer/counter pulse
    
    TCCR1B |= (1<< CS12);
    //TCCR1B &= ~(1<<CS10) & ~(1<<CS12); //setter prescaler til clk/8 

    //TIMSK0 = (1 << TOIE0); // Mulligjør interupts for hver overflow

    ICR1 = 1250;
}

void pwm_signal(uint16_t gass){
    OCR1A = gass;
}