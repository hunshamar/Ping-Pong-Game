
#ifndef F_CPU
#define F_CPU 4915200UL
#endif

#include <stdio.h>
#include <avr/io.h>
#include "Uart_driver.h"
#include <util/delay.h>
#include "SRAM.h"
#include "adc_driver.h"
#include <util/delay.h>
#include "joystick.h"

int main(){
    
    
    
    uart_init(9600);
    MCUCR = (1<<SRE);
    SFIOR = (1<<XMM2);
    
    //uart_transmit(8);
    //uart_recieve();
    
    printf("HEI \n\r");
    coord_sample cs = joy_init();
    //direction where = get_direction(get_joy_coords_x,get_joy_coords_y);
    while(1){
        //printf("Joystick. X = %d  Y= %d  \n\r", get_joy_coords_x(cs), get_joy_coords_y(cs));
        printf("Direction is: %d and %d  \n\r", get_direction(get_joy_coords_x,get_joy_coords_y).x, get_direction(get_joy_coords_x,get_joy_coords_y).y);
        _delay_ms(200);
    }

    //adc_test();
    //printf(" SVEIS ");
    //_delay_ms(2000);
    //SRAM_test();
    //_delay_ms(3000);
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

    /*while(1){if(y <= 10 && y >= -10){
        where.y = NEUTRAL;
    }  
    else if(y > 0){
        where.y = RIGHT;
    }
    else if(y > 0 ){
        where.y = LEFT;
    }
}
        PORTB = (1 << PB1);
        _delay_ms(1000);

        PORTB = (0 << PB1);
        _delay_ms(1000);
    }*/
    return 0;
}