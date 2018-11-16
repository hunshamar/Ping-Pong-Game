
#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <stdio.h>
#include <avr/io.h>
#include "Uart_driver.h"
#include <util/delay.h>
#include "spi_driver.h"
#include "can_driver.h"
#include "mcp2515.h"
#include "pwm_driver.h"
#include "adc_driver.h"
#include "TWI_Master.h"
#include "dac_driver.h"
#include "joystick.h"
#include "motor_controller.h"
#include "pi.h"
#include "solenoid.h"
#include "game.h"
//#include "interrupt.h"

int main(){
    uart_init(9600);
    pwm_init();
    solenoid_init();
    
    
    //uart_transmit(8);
    //uart_recieve();

    printf("HEI \n\r");




    sei();
    adc_init();
    dac_init();
    can_init();

    _delay_ms(100);
    joystick_init();
    //interrupt_init();
    /*
    int tall = 0;
    while(1){
        printf("før \n\r");
        send_voltage(125);
        printf("Etter? \n\r");
            /*
    
        
        
        
        /*
        if(adc_counter()){
            tall++;
            printf("tall: %d \n\r", tall);
            while(adc_counter()){
            }
            _delay_ms(50);
        }*/
      
        

    
    /*
    pwm_signal(100);  
    
    _delay_ms(40);

    */



    motor_controller_init();

    PORTH &= ~(1 << PINH1); //left direction
    send_voltage(100);
    _delay_ms(1000);
    


    message nah;
    nah.ID = 2;
    nah.length = 1;
    nah.data[0] = 1;
    
    PIData_t pi;
    PI_Init(250,10,&pi);


    int i = 0;
    while(1){
    
    
    //printf("Encoderverdien vår er: %d \n\r",get_encoder_data());

    //printf("MCP_CANCTRL, loop back?: %d \n\r\n\r",mcp2515_read(MCP_CANCTRL));
    
    int position = (get_encoder_data()*-1)/87.65;


    uint16_t adc_input = adc_read();
    message msg;
    msg.ID = 1;
    msg.length = 2;
    msg.data[0] = (adc_input>>8);
    msg.data[1] = (adc_input);

    
    motor_controller_cont(PI_Controller((int)(slider_get_right_pos()), position, &pi));
    printf("  Slider right: %d ",slider_get_right_pos());
    printf("    Encoder: %d ",position);
    printf("    Error er: %d \n\r",slider_get_right_pos()-position);
    printf("adc input %d %d", msg.data[0], msg.data[1]);
    if(joystick_get_button_status()){
        printf("Shoot! \n\r");
        solenoid_shoot();
    }
    //send_voltage(100);
    
    if (mcp2515_check_bit(MCP_CANINTF,1)){ //Fått ny melding?
        RECIEVED = can_read();
    }

    can_write(msg);
    /*while(!adc_counter()){

    printf(adc_counter());
    
    game_play(MODE_SPEED);
    }
    

    /*
    printf("X: %d  y: %d  jb: %d  ls: %d  rs: %d  lsb: %d  rsb: %d  mag: %d   \n\r",
        joystick_get_raw_x(), joystick_get_raw_y(), joystick_get_button_status(), slider_get_left_pos(),
        slider_get_right_pos(), slider_get_left_button_status(), slider_get_right_button_status(), joystick_get_raw_x()-x_offset
        );
    */
    //motor_controller_cont(PI_Controller(joystick_get_raw_x()-x_offset, get_encoder_data()*0.1, &pi));
    //printf("Reggis output: %d \n\r",PI_Controller(joystick_get_raw_x()-x_offset, get_encoder_data()*0.1, &pi));
    //joystick_to_pwm(joystick_get_y());
    //motor_controller_cont(50);
    //motor_controller_cont(joystick_get_x());
    /*
    printf("\n\r");
    printf("Joystick x: %d",joystick_get_raw_x());
    printf("Encoderverdiene våre er som følger: %d \n\r",get_encoder_data());
    printf("Regulatorverdiene våre er som følger: %d \n\r", PI_Controller(0, get_encoder_data(), &pi));
    */
    
    }
    
    return 0;
}