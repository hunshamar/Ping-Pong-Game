#include "oled.h"
#include "menu.h"
int line = 0;




volatile char* oled_command_channel = (char * ) 0x1000;
volatile char* oled_data_channel = (char * ) 0x1200;

void write_command(uint8_t command){
    oled_command_channel[0] = command;
}

void oled_write_data(int channel, int data){

    oled_data_channel[channel] = data;
    
}

void oled_write_char(uint8_t character){

    for (int i = 0; i < 8; i++){

        oled_data_channel[0] = pgm_read_byte(&font8[character-32][i]);
    }

}

void oled_write_char_font(uint8_t character, uint8_t font_size){

    switch(font_size)
    {
        case 8:
            for (int i = 0; i < 8; i++){

                oled_data_channel[0] = pgm_read_byte(&font8[character-32][i]);
            }
            break;

        

        case 5:
            for (int i = 0; i < 5; i++){

                oled_data_channel[0] = pgm_read_byte(&font5[character-32][i]);
            }
            for (int i = 0; i < 3; i++){

                oled_data_channel[0] = pgm_read_byte(&font5[' '-32][i]);
            }
            break;

        case 4:
            for (int i = 0; i < 4; i++){

                oled_data_channel[0] = pgm_read_byte(&font4[character-32][i]);
            }
            for (int i = 0; i < 4; i++){

                oled_data_channel[0] = pgm_read_byte(&font5[' '-32][i]);
            }
            break;
        default:
            break;

    }
}




void oled_print(char* s){

    int i= 0;
    while(s[i] != 0){

        if(s[i] == '\n'){

            if(line == 6)
                line = 0;
            else
                line += 1;
            write_command(0b10110000 + line); 
	write_command(0x21); // set column address
	write_command(0x00);		// start address
	write_command(0x7f);		// end address
        }
        else{

        oled_write_char_font(s[i], 5);
        }
        i++;
    }

}

void oled_print_font(char* s, uint8_t font_size){
    
    int i= 0;
    while(s[i] != 0){

        if(s[i] == '\n'){

            if(line == 6)
                line = 0;
            else
                line += 1;
            write_command(0b10110000 + line); 
	        write_command(0x21); // set column address
	        write_command(0x00);		// start address
	        write_command(0x7f);		// end address
        }
        else{

        oled_write_char_font(s[i], font_size);
        }
        i++;
    }

}

void oled_clear(){
    for (int i = 0; i < 8; i++){

        //write_command(0b10110000 + i);
        for (int j = 0;j<128;j++){
            *oled_data_channel = 0x00;
        }
    }

}

void oled_fill(){
    for (int i = 0; i < 8; i++){
        

        write_command(0b10110000 + i);
        for (int i = 0;i<128;i++){
            oled_data_channel[i] = 0xFF;
        }
    }
}


   

void oled_init() 
  { 
    write_command(0xae); // display off
	write_command(0xa1); // map segments to  0-128 in instead of 128-256
	write_command(0xda); // common pads hardware: alternative
	write_command(0x12);
	write_command(0xc8); // common output scan direction:com63~com0
	write_command(0xa8); // multiplex ration mode:63
	write_command(0x3f);
	write_command(0xd5); // display divide ratio/osc. freq. mode
	write_command(0x80);
	write_command(0x81); // contrast control
	write_command(0x50);
	write_command(0xd9); // set pre-charge period
	write_command(0x21);
	write_command(0x20); // set memory addressing mode
	write_command(0x00); 		
	write_command(0x21); // set column address
	write_command(0x00);		// start address
	write_command(0x7f);		// end address
	write_command(0x22); // set page address
	write_command(0x00); 	// start address
	write_command(0x07); 	// end address
	write_command(0xdb); // VCOM deselect level mode
	write_command(0x30);
	write_command(0xad); // master configuration
	write_command(0x00);
	write_command(0xa4); // out follows RAM content
	write_command(0xa6); // set normal display
    write_command(0xaf); // display on
} 





int get_line(int y){

    int line;
    if (y == 0)
        line = 1;

    else if (y%8 == 0)
        line = y/8;
    else {
        line = ((double)(y))/8;
        line += 1; 
    }
    return line;
}

void oled_write_to_pixel(int x, int y){
    
    if (x > 128 || y > 64)
        return;

    int line = get_line(y);

    int subline = get_line(y%8);   

    int word = (2 << subline);


    write_command(0b10110000 + line -1);

    printf("x: %d, y: %d, line: %d, a: %d\n\r", x,y,line,subline);
    
    for(int i = 0; i < x-1; i++){
        oled_write_data(i,0);
    }

    oled_write_data(x-1,word);
}

