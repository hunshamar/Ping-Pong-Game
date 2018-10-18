#include "spi_driver.h"

void spi_init(void){
/* Set MOSI and SCK output, all others input */
DDRB |= (1<<PB0)|(1<<PB7)|(1<<PB2)|(1<<PB1);        //DDRB = (1<<DDB5)|(1<<DDB7)|(1<<DDB4);

/* Enable SPI, Master, set clock rate fck/16 */
SPCR |= (1<<MSTR)|(1<<SPR0);
SPCR |= (1<<SPE);
}

void spi_master_write(char cData){
/* Start transmission */
SPDR = cData;
/* Wait for transmission complete */
while(!(SPSR & (1<<SPIF))){

    }//do nothing
}
char spi_master_read(){
    spi_master_write(0xFF); //Sender dummy byte
    return SPDR; //returner registeret SPDR
}