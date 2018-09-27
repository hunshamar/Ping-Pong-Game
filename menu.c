#include "menu.h"

void menu(){

    char* str1 = "\n->forste\n  andre\n  tredje\n \n \n \n";
    char* str2 = "\n  forste\n->andre\n  tredje\n \n \n \n";
    char* str3 = "\n  forste\n  andre\n->tredje\n \n \n \n ";
    char* sub_str1 = "\n Dette er faen\n meg \n forste \n menyelement!  \n \n \n";
    char* sub_str2 = "\n oioi er dette\n andre?? \n \n \n \n \n";
    char* sub_str3 = "\n wow dette er \n tredje jo  \n \n \n \n \n";


    char* menu[3] = {str1, str2, str3};
    char* sub_menu[3] = {sub_str1,sub_str2,sub_str3};

    int pos = 0;
    oled_clear();
    oled_print(menu[pos]);
    coord_sample cs = joy_init();
    
    while(1){
        //oled_init();
        if(get_direction(get_joy_coords_x(cs),get_joy_coords_y(cs)) == 4){
            printf("%d\n\r", pos%3);
            pos += 1;
            oled_clear();
            oled_print(menu[pos%3]);
            while(get_direction(get_joy_coords_x(cs),get_joy_coords_y(cs))!= 0){
                _delay_ms(50);
            }
        }
        else if (get_direction(get_joy_coords_x(cs),get_joy_coords_y(cs)) == 3){
            printf("%d\n\r", pos%3);
            pos -= 1;
            if(pos == -1){
                pos = 2;
            }
            oled_clear();
            oled_print(menu[pos%3]);
            while(get_direction(get_joy_coords_x(cs),get_joy_coords_y(cs))!= 0){
                _delay_ms(50);
            }
        }

        if(get_direction(get_joy_coords_x(cs),get_joy_coords_y(cs)) == 1){
            oled_clear();
            oled_print(sub_menu[pos%3]);
            while(!get_joystick_button_status()){

            }
            oled_clear();
            oled_print(menu[pos%3]);
        }
        


        
    }
}