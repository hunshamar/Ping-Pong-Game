
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

int main(){
    PIData_t pi;
    PI_Init(1,0,&pi);
    uart_init(9600);
    pwm_init();
    

    //uart_transmit(8);
    //uart_recieve();

    printf("HEI \n\r");


    message msg;

    sei();
    adc_init();
    dac_init();
    can_init();

    _delay_ms(100);
   joystick_init();
    
    /*
    int tall = 0;
    while(1){
        printf("før \n\r");
        send_voltage(125);
        printf("Etter? \n\r");
        
        
        
        
        
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

   while(1){
    
    
    can_init();

    _delay_ms(60);

    /*printf("x: %d  y: %d  jb: %d  ls: %d  rs: %d  lsb: %d  rsb: %d  mag: %d   \n\r",
        joystick_get_raw_x(), joystick_get_raw_y(), joystick_get_button_status(), slider_get_left_pos(),
        slider_get_right_pos(), slider_get_left_button_status(), slider_get_right_button_status(), joystick_get_raw_x()-x_offset
        );*/
    
    //motor_controller_cont(PI_Controller(joystick_get_raw_x()-x_offset, get_encoder_data(), &pi)+x_offset);
    joystick_to_pwm(joystick_get_y());
    motor_controller_cont(joystick_get_x());
    printf("\n\r");
    printf("Joystick x: %d",joystick_get_raw_x());
    printf("Encoderverdiene våre er som følger: %d \n\r",get_encoder_data());
    printf("Regulatorverdiene våre er som følger: %d \n\r", PI_Controller(0, get_encoder_data(), &pi));

    }
    
    return 0;
}