#define FOSC 4915200 //clock speed
#define BAUD 9600

void uart_init(unsigned int pin);

void uart_transmit(uint8_t data);

uint8_t uart_recieve();