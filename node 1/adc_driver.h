#ifndef __ADC_DRIVER_H__
#define __ADC_DRIVER_H__
#include <stdint.h>

typedef enum {
    CHANNEL_1 = 0b00000100,
    CHANNEL_2 = 0b00000101,
    CHANNEL_3 = 0b00000110,
    CHANNEL_4 = 0b00000111,
} adc_channel_t;

uint8_t read_channel(adc_channel_t channel);

#endif /* __ADC_DRIVER_H__ */