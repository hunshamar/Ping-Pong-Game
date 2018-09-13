#include <stdlib.h>
#include<stdint.h>
#include <stdio.h>
#include "adc_driver.h"

void adc_test(){
    volatile char *ext_adc = (char *) 0b010000000000; // Start address for the ADC
    *ext_adc = 50;
    printf("Checking ADC chip select. Does the diode turn off?");
    while(1){
        uint8_t some_value = ext_adc[0];
    }
}