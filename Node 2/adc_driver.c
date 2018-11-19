#include "adc_driver.h"
#include "avr/io.h"

void adc_init(){
    DDRF &= ~(1 << PF2); //Bruker pin pf2 som input
    ADCSRA |= (1 << ADEN); //Enabler ADC funksjonen på Arduionoen
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); //Setter prescalar bits til å ha en division factor på 128 mellom XTAL frekvensen og input klokka
    ADMUX &= ~(1 << ADLAR); //For å få dataregistrene på format vi ønsker, ATmega 2560 s. 286
    ADMUX |= (1 << REFS1) | (1 << REFS0); //setter spenningsreferansen til 2.56V
 }


uint16_t adc_read(){
    uint16_t data = 0;
    ADMUX |= (1 << MUX1); //Choose Single ended input with ADC2
    ADCSRA |= (1<< ADSC); //start conversion;
    while(bit_is_set(ADCSRA,ADSC)); //wait for registers loaded;
    uint8_t datalow = ADCL; //Reading from register
    uint16_t datahigh = ADCH; 
    data = datalow+ (datahigh <<8 ); //combining data
    return data;
}

uint8_t adc_counter(){
    if(adc_read() < 100){
        return 1;
    }
    return 0;
}