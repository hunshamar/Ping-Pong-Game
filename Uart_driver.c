
#include <stdint.h>
#include "Uart_driver.h"
#include <avr/io.h>



void uart_transmit(uint8_t data){
    while(!(UCSR0A & (1<<UDRE0))){
        //Mens flagget er av 
    }
    //send message
    UDR0 = data;
}


uint8_t uart_recieve(){
    UCSR0B = (1<<RXEN0);
    while(!( UCSR0A & (1<<RXC0))){
        //Venter på noe i registeret
    }
    return UDR0;
}

void uart_init(unsigned int pin){
    
    //set baud rate
    UBRR0H = (pin>>8);
    UBRR0L = pin;
    //Enable r/t
    UCSR0B = (1<<RXEN0) | (1<<TXEN0);
    //set frame format
    UCSR0C = (1<<USBS0) | (1<<URSEL0) | (1<<UCSZ10) | (1<<UCSZ00);

    fdevopen(&uart_transmit,&uart_recieve);

}
