#include "pwm_driver.h"

void pwm_init(){
    DDRB |= (1<<PINB5); // Setting PB5 as input
 
    TCCR1A |= (1 << WGM11);
    TCCR1B |=  (1 << WGM12) | (1 << WGM13); //Put the unit in mode 14, fast PWM. Checkout datasheet page 145 for more info

    TCCR1A |= (1 << COM1A1); 
    TCCR1A |= (1 << COM1A0); //Enables compare output mode, so that 0C1A is comparator to timer/counter pulse
    
    TCCR1B |= (1<< CS12); //puts prescaler to clk/256

    ICR1 = 1250; //1125 is highest -> 2.1 ms , 1195 lowest -> 0.9 ms
}

int pwm_signal(uint16_t gass){ //moves the servo
    if (gass >= PWMMIN && gass <= PWMMAX) {
        OCR1A = gass;
        return 1;
    }
    else{ 
        printf("err");
        return -1;
    }
}