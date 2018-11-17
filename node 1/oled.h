#ifndef __OLED_H__
#define __OLED_H__
#include <stdio.h>
#include <avr/io.h>
#include "fonts.h"
#include <avr/pgmspace.h>


void oled_write_char(uint8_t character);
void oled_write_data(int channel, int data);
void write_command(uint8_t command);
void oled_init();
void oled_clear();
void oled_fill();
void oled_print(char* s);


int get_line(int y);

void oled_write_to_pixel(int x, int y);
void write_data(char character);



#endif