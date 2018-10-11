#include <avr/io.h>


void spi_init(void);
void spi_master_write(char cData);
char spi_master_read();