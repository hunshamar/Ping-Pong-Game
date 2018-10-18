
#include <stdint.h>
#include "Uart_driver.h"
#include <avr/io.h>


#ifndef F_CPU
#define F_CPU 16000000UL
#endif


int uart_transmit(char data,FILE* fil){
    while(!(UCSR0A & (1<<UDRE0))){
        //Mens flagget er av 
    }
    //send message
    UDR0 = data;
    return 0;
}


int uart_recieve(FILE* fil){
    //UCSR0B = (1<<RXEN0); //tror det er å sette recieverflagg
    if(!(UCSR0A & (1<<RXC0))){
        return 0;
        //Venter på noe i registeret
    }
    return UDR0;
}

void uart_init(unsigned int baud){
    
    
    int bd = 0.15*((long)F_CPU/((long)(16*baud)) -1);
    //set baud rate
    UBRR0H = (bd>>8);
    UBRR0L = bd;
    



    //Enable r/t
    UCSR0B = (1<<RXEN0) | (1<<TXEN0);
    //set frame format
    UCSR0C = (1<<USBS0) | (3<<UCSZ00);

    fdevopen(uart_transmit,uart_recieve);

}
