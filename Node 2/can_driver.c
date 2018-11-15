#include "can_driver.h"

void can_init(){

    spi_init();

    mcp2515_reset();

    mcp2515_bit_modify(0x60, MCP_RXB0CTRL, 0b01100000); //recieve buffer 0 control 
    mcp2515_bit_modify(0b1, MCP_CANINTE, 0b00000001); //sier at RXoIF flagget skal bli høyt ved å sette RX0IE verdien i CANINTE registeret høyt 
    mcp2515_bit_modify(0b11100000,MCP_CANCTRL,MODE_NORMAL); //sett til normalmode


    //printf("MCP_CANCTRL, loop back?: %d \n\r\n\r",mcp2515_read(MCP_CANCTRL));
    

}


void can_write(message msg){
     //litt usikker

    /** Skriver ID (adressen) til rett registre, ID er på 11 bit hvor hele SIDH registeret skal være fullt, mens de tre minste er MSB i SIDL **/

    mcp2515_write(MCP_TXB0SIDH, (uint8_t)(msg.ID >> 3)); //8 MSB
    
    mcp2515_bit_modify(0b11100000, MCP_TXB0SIDL, (uint8_t)(msg.ID << 5));  //3 LSB

    /** Setter data lengden i DLC registerets 4 LSB. Uten å endre resten av registeret **/
     mcp2515_bit_modify(0b00001111,MCP_TXB0DLC,msg.length);

    /** Dataoverføring, opptil 8 bytes med data, skrives til register TDXB0D0 til TDXB0D7. **/

        
        for (int length = 0; length < 8; length++){
            mcp2515_write(MCP_TXB0D0 + length, msg.data[length]);
        }
    
    
    mcp2515_rts(1);
    printf("RtS i funk: %d \n\r", mcp2515_check_bit(MCP_TXB0CTRL,3));


}

int can_transmit_complete(){
    return mcp2515_check_bit(MCP_TXB0CTRL,3);
}


message can_read(){

    message msg;
    if(mcp2515_check_bit(MCP_CANINTF,1)){
        uint8_t ID_high = mcp2515_read(MCP_RXB1SIDH);
        uint8_t ID_low = mcp2515_read(MCP_RXB1SIDL);
        msg.ID = (ID_high << 3) | (ID_low >> 5); //11 bit adresse

        msg.length = mcp2515_read(MCP_RXB1DLC) & 0x0F; //leser 4 lsb

        /*
        printf("\n\rID mottatt: %d %d \n\r", (uint8_t)(msg.ID >> 3), (uint8_t)(msg.ID << 5) );
        printf("data lengde mottatt: %d \n\r", msg.length);*/
        

        if(msg.length > 8)
            msg.length = 8;

        //printf("Data mottatt: ");
        for (int l = 0; l < msg.length; l++){
            msg.data[l] = mcp2515_read(MCP_RXB1D0 + l);
            //printf(" %d ", msg.data[l]);
        }
        mcp2515_bit_modify(00000001,MCP_CANINTF,0b0); //Skrur av recieved-flagget


    }
    else{ 
        printf("can error \n\r");

    }
    //printf("\n\r----------\n\r\n\r ");
    //    printf("FERDIG");

    return msg;
}
