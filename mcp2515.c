#include "mcp2515.h"

void slave_select(){
    PORTB &= ~(1<< PB4);
}

void slave_deselect(){
    PORTB |= (1<< PB4);
}

uint8_t mcp2515_read(uint8_t address){
    uint8_t result;
    slave_select(); 
    spi_master_write(MCP_READ);
    spi_master_write(address); //send address
    result = spi_master_read();

    slave_deselect();
    return result;
}

void mcp2515_write(uint8_t address, uint8_t data){
    slave_select(); //Select CAN

    spi_master_write(MCP_WRITE);
    spi_master_write(address);
    spi_master_write(data);

    slave_deselect();
}

int mcp2515_check_bit(uint8_t address, uint8_t bit){
    uint8_t reggie = mcp2515_read(address);
    return reggie &(1<<bit);
}

void mcp2515_rts(uint8_t rts){
    slave_select();
    spi_master_write(rts); //Velger mellom TXB(0-2)CTRL ved å sette TXREQ bittet høyt
    slave_deselect();
}

uint8_t mcp2515_read_status(){
    slave_select();
    spi_master_write(MCP_READ_STATUS);
    uint8_t result = spi_master_read();
    spi_master_write(0x00);
    slave_deselect();
    return result;
}


uint8_t mcp2515_reset(){

    slave_select();
    spi_master_write(MCP_RESET);
    slave_deselect();

}

void mcp2515_bit_modify(uint8_t mask, uint8_t adress, uint8_t data){
    

    slave_select();

    spi_master_write(MCP_BITMOD);
    spi_master_write(adress);
    spi_master_write(mask);
    spi_master_write(data);

    slave_deselect();



}