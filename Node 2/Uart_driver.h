#include <stdio.h>

void uart_init(unsigned int pin);

int uart_transmit(char data,FILE* fil);

int uart_recieve(FILE* fil);