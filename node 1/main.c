
#ifndef F_CPU
#define F_CPU 4915200UL
#endif

#include <stdio.h>
#include <avr/io.h>
#include "Uart_driver.h"
#include <util/delay.h>
#include "SRAM.h"
#include "adc_driver.h"
#include "joystick.h"
#include "oled.h"
#include "menu.h"
#include "spi_driver.h"
#include "mcp2515.h"

#include "can_driver.h"


int main(){
    
    
    
    uart_init(9600);
    MCUCR = (1<<SRE);
    SFIOR = (1<<XMM2);

    //uart_transmit(8);
    //uart_recieve();
    
    printf("HEI \n\r");

    joystick_init();

    menu();
    
    /*

    message msg;


    can_init();


    msg.ID = 1;
    msg.length = 7;


    uint8_t mess[7] = "Hallo!!"; 
    for (int i = 0; i < msg.length; i++){
        msg.data[i] = mess[i];
    }
    while(1){
    can_write(msg);

    message recieved = can_read();
    }

    */
/*
int asd = 0;
while(1){
    can_write(msg); 
    asd+=1;
    if (asd%1000 == 0){
        printf("sender\n\r");
        asd = 0;
    }
}*/

    //direction where = get_direction(get_joy_coords_x,get_joy_coords_y);
    



    oled_init();
    spi_init();
    /*
    while(1){
        //mcp2515_write(0x0F,'i');
        //printf("HER ERN: %c \n\r", mcp2515_read(0x0F));
        
        mcp2515_read_status();

    }*/


    menu();

    while(1){


        //oled_write_to_pixel(20,20);
        _delay_ms(100);

        /*
        for (int i = 0; i<64;i++){
            _delay_ms(20);
            oled_write_data(i,0x00);
        }

        for (int i = 64; i<128;i++){
            _delay_ms(20);
            oled_write_data(i,0xFF);
        }*/

        /*
        int x =  get_joy_coords_x(cs);
        int y =  get_joy_coords_y(cs);

        printf("slider pos: %d\n\r", get_right_slider_pos());

        
        printf("Joystick. X = %d  Y= %d     ", x, y);



        printf("Angle: %d   ", get_angle(x, y));

        printf("Direction is: %s\n\r", dir_to_string(get_direction(x,y)));   //(get_joy_coords_x(cs), get_joy_coords_y(cs)));

        */
         // {0b01111100,0b01111110,0b00010011,0b00010011,0b01111110,0b01111100,0b00000000,0b00000000}

     
    }

    //adc_test();
    //printf(" SVEIS ");
    //_delay_ms(2000);
    SRAM_test();
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