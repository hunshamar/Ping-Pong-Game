

#include <stdio.h>
#include <avr/io.h>
#include "Uart_driver.h"
#include <util/delay.h>

int main(){
    
    
    uart_init(9600);
    //uart_transmit(8);
    //uart_recieve();
    
    printf("hallo");
    while(1){
        char letter = 0;
        while(letter ==0){
            letter = uart_recieve();
    }   
        letter+= ('A'-'a');
        uart_transmit(letter);
}


    
    //inputs
    DDRA = 0x00;

    //Gjør til output
    DDRB = 0xFF;

    /*while(1){
        PORTB = (1 << PB1);
        _delay_ms(1000);

        PORTB = (0 << PB1);
        _delay_ms(1000);
    }*/


    return 0;
}