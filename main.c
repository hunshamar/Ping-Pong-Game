
#ifndef F_CPU
#define F_CPU 4915200UL
#endif

#include <stdio.h>
#include <avr/io.h>
#include "Uart_driver.h"
#include <util/delay.h>
#include "SRAM.h"

int main(){
    
    
    
    uart_init(9600);
    //uart_transmit(8);
    //uart_recieve();
    
    printf("HEI \n\r");
    MCUCR |= (1<<SRE);
    printf(" SVEIS ");
    _delay_ms(2000);
    SRAM_test();
    _delay_ms(3000);
    for (int i = 0; i < 100; i++){
        printf("%d ", i);
        _delay_ms(10);
    }
    /*
    while(1){a
        char letter = 0;
        while(letter ==0){
            letter = uart_recieve();
    }   
        letter+= ('A'-'a');
        uart_transmit(letter);
}
*/
    /*
    while(1){

        uart_transmit('b');
        _delay_ms(1000);
    }*/

    //inputs
    //DDRA = 0x00;

    //Gjør til output
    //DDRB = 0xFF;

    /*while(1){
        PORTB = (1 << PB1);
        _delay_ms(1000);

        PORTB = (0 << PB1);
        _delay_ms(1000);
    }*/


    return 0;
}