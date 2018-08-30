
#ifndef F_CPU
#define F_CPU 4915200UL
#endif

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include "Uart_driver.h"

int main(){
    
    uart_init(9600);
    uart_transmit(8);

    printf("%d  test \n\n\n\n", uart_recieve());
    //inputs
    DDRA = 0x00;

    //Gjør til output
    DDRB = 0xFF;

    while(1){
        PORTB = (1 << PB1);
        _delay_ms(1000);

        PORTB = (0 << PB1);
        _delay_ms(1000);
    }


    return 0;
}