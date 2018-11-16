#include <stdio.h>
#include <avr/io.h>
#include <stdlib.h>
#include <stdint.h>
#include <util/delay.h>
#include "adc_driver.h"

uint8_t read_adc_channel(adc_channel_t channel){
    volatile char* adc_channel = (char * ) 0x1400;

    //By sending this to ADC we check single-ended voltage diff on selected channel
    adc_channel[0] = channel;

    //Waiting for ADC to sample
    _delay_ms(20);

    //Retrieving value from ADC
    uint8_t retrieved_value = adc_channel[0];
}