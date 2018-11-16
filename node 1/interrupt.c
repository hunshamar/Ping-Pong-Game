#include "interrupt.h"

void interrupt_init(){

    /*Interrupt to send joystick to node 2*/
    ETIMSK |= (1<<TOIE3) | (1<<OCIE3A); //Overflow will trigger interrupt 3 and compare A Match interrupt enabled
    TCCR3A |= (1<<COM3A0); //Setter CTC mode
    OCR3A = 100400;
    TCCR3B |=  (1<<WGM32) | (1 << CS31) ; //Using prescalar 8
    TCNT3 = 0x00; //Setting counting registers initial value to 0
    
    /*Interrupt to terminate game*/
    DDRD |= (1<<PD2); //Using the PD2 as input
    PORTD |= (1<<PD2); // Putting the pin PD2 as high
    GICR |= (1<<INT0); // Enable interrupt on PIN0 
    MCUCR |= (1<<ISC01); //Demanding a falling edge on the interrupt pn PD2
}

ISR(TIMER3_COMPA_vect){
    
    //Declare variables
    message msg;
    msg.ID = 1;
    msg.length = 7;
    int i = 0;

    msg.data[0] = read_adc_channel(CHANNEL_1); //x
    msg.data[1] = read_adc_channel(CHANNEL_2); //y
    msg.data[2] = joystick_get_button_status(); //joystickknapp
    msg.data[3] = slider_get_left_pos();
    msg.data[4] = slider_get_right_pos();
    msg.data[5] = slider_get_left_button_status();
    msg.data[6] = slider_get_right_button_status();


    can_write(msg);

}

ISR(INT0_vect){
    printf("Terminate game? INT funker");
    mcp2515_bit_modify(0b00000011,MCP_CANINTF,0b00000000);
}