#include "motor_controller.h"
#include <util/delay.h>

void motor_controller_init(){
    DDRH |= (1 << DDH4) | (1 << DDH1); // Enable motorbox with pin4 and direction with pin1
    DDRH |= (1<<DDH3) | (1<<DDH5) | (1 << DDH6); //enable encoder: PH3 = SEL, PH5 = !OE, PH6 = RST
    PORTH |= (1 << PORTH4); //Enable on
    
}


void motor_controller_signal(int speed){ //speed er 0 i 0, høyre er positiv, og venste er negativ. -100 til 100.
    if(speed > 10){
        PORTH |= (1<<PINH1); //right direction
        send_voltage(speed);

    }else if(speed < -10){
        send_voltage(speed*(-1));
        PORTH &= ~(1 << PINH1); //left direction

    }else{
        send_voltage(0);
    }
}

uint16_t motor_controller_get_encoder_data(){
    uint16_t data;
    cli();
    DDRK = 0x00;
    PORTH &= ~(1<<PH5); //enable output of encoder
    PORTH &= ~(1<<PH3); //set SEL low to read high byte
    _delay_ms(20);
    data = (PINK <<8);
    PORTH |= (1<<PH3); //set SEL HIGH to read low byte
    _delay_ms(20);
    data |= PINK;
    //PORTH &= ~(1<<PH6); //toggle reset
    _delay_ms(20);
    PORTH |= (1<<PH6);
    PORTH |= (1 << PH5); //output disable
    sei();

    return data;
}