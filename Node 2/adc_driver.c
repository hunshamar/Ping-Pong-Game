#include "adc_driver.h"

void adc_init(){

    DDRB |= (1 << PB6); //Bruker pin f2 som input

    ADCSRA |= (1 << ADEN); //Enabler ADC funksjonen på Arduionoen

    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); //Setter prescalar bits til å ha en division factor på 128 mellom XTAL frekvensen og input klokka
 
    ADMUX |= (1 << REFS1) | (1 << REFS0); //setter spenningsreferansen til 2.56V
 }

 int get_joystick_button_status(){
    if (bit_is_set(PINB, PB6))
        return 0; //active low
    else   
        return 1;
}