#include "menu.h"

void oled_print_node_and_children(menu_element element, int elem_nr){
    oled_print(element.print);
    int i = 0;
    oled_print("\n \n");
    while( element.children[i] != NULL){
        if((i == elem_nr) && (element.nr_children != -1)){
            oled_print("->");
        }
        
        else if(element.nr_children >= 0){
            oled_print("  ");
        }
        oled_print(element.children[i]->print);
        oled_print("\n");
        i++;
    }
    i = 6-i;
    while(i != 1 && element.nr_children != -1){
        oled_print("\n");
        i--;
    }
}

void update_leaderboard(int score){
    int temp_leaderboard[5];
    int placing_index;
    for (int i = 0; i < 5; i++){
        if(LEADERBOARD[i]<score){
            placing_index = i;
        }
        break;
        }
    for (int j = 0; j < placing_index; j++){
        temp_leaderboard[j]=LEADERBOARD[j];
    }
    temp_leaderboard[placing_index]=score;
    for (int n = placing_index+1; n < 4; n++){
        temp_leaderboard[n]=LEADERBOARD[n+1];
    }
    for(int m = 0; m < 5; m++){
        LEADERBOARD[m] = temp_leaderboard[m];
    }
}


void visual_menu(){

    int Leaderboard[5] = {0,0,0,0,0};

    joystick_init();

    menu_element main_menu;
    menu_element rookie;
    menu_element expert;
    menu_element game_mode;
    menu_element credits_text;
    menu_element highscore;

    menu_element play_game;
    play_game.parent = &main_menu;
    play_game.children[0] = &expert;
    play_game.children[1] = &rookie;
    play_game.nr_children = 2;
    play_game.print = "Play game";
/*
    game_mode.parent = &play_game;
    game_mode.children[0] = &rookie;
    game_mode.children[1] = &expert;
    game_mode.nr_children = 2;
    game_mode.print = "Select gamemode";
*/
    rookie.parent = &play_game;
    rookie.children[0] = NULL;
    rookie.print = "Rookie";

    expert.parent = &play_game;
    expert.print = "Expert";

    menu_element leaderboard;
    leaderboard.parent = &main_menu;
    leaderboard.children[0] = &highscore;
    leaderboard.nr_children = -1;
    leaderboard.print = "Leaderboard";


        LEADERBOARD[0] = 1000;
    LEADERBOARD[1] = 77;
    LEADERBOARD[2] = 55;

    char first_place[5]; 
    char second_place[5];
    char third_place[5];

    char string[100];


    itoa(LEADERBOARD[0], first_place, 10);
    itoa(LEADERBOARD[1], second_place, 10);
    itoa(LEADERBOARD[2], third_place, 10);

    strcpy(string, "1. ");
    strcat(string, first_place);
    strcat(string, "\n2. ");
    strcat(string, second_place);
    strcat(string, "\n3. ");
    strcat(string, third_place);


    

    highscore.parent = & leaderboard;
    highscore.children[0] = NULL;
    highscore.nr_children = -1;
    highscore.print = string;

    menu_element credits;
    credits.parent = &main_menu;
    credits.children[0] = &credits_text;
    credits.nr_children = -1;
    credits.print = "Credits";

    credits_text.parent = &credits;
    credits_text.children[0] = NULL;
    credits_text.nr_children = -1;
    credits_text.print = "Eilef \nMartin \nAsgeir \n In remembrance of\n heroic effort";

    main_menu.parent = NULL;
    main_menu.children[0] = &play_game;
    main_menu.children[1] =  &leaderboard;
    main_menu.children[2] = &credits;
    main_menu.print = " Main menu";
    main_menu.nr_children = 3;

    int elem_nr = 0;
    oled_clear();
    oled_print_node_and_children(main_menu,elem_nr);

    menu_element current_menu_element = main_menu;
    int current_pos = 0;
    int seconds;
    int game = 0;
    
    while(1){

        message game_mode;
        game_mode.ID = 2;
        game_mode.length = 6;
        game_mode.data[0] = 1;


        //if(joystick_get_direction() == UP){ //Joystick
        if(slider_get_left_button_status() && current_pos != 0 && !slider_get_right_button_status()&& current_menu_element.nr_children != -1){
            // trykk fra left button && ikke øverste element && ikke samtidig med right button && det ikke er credits
            oled_clear();
            current_pos--;
            oled_print_node_and_children(current_menu_element,current_pos % current_menu_element.nr_children);
            //while(joystick_get_direction()!= NEUTRAL){
            while(slider_get_left_button_status()){
                _delay_ms(50);
                }
        }
        
        //if(joystick_get_direction() == DOWN){
        if(slider_get_right_button_status() && current_pos != current_menu_element.nr_children - 1 && !slider_get_left_button_status() && current_menu_element.nr_children != -1){
            // trykk fra right button && ikke laveste elementet && ikke samtidig med left button && ikke credits siden
            oled_clear();
            current_pos++;
            
            oled_print_node_and_children(current_menu_element,current_pos%current_menu_element.nr_children);
            //while(joystick_get_direction()!= NEUTRAL){
            while(slider_get_right_button_status()){
                _delay_ms(50);}
        }
        
        //if((joystick_get_direction() == RIGHT) && ((current_menu_element.children != NULL))){
        if(joystick_get_button_status()){
            oled_clear();
            current_menu_element = *current_menu_element.children[current_pos];
            current_pos = 0;
            oled_print_node_and_children(main_menu,1);

            if(&current_menu_element == &rookie){
                game_mode.data[0] = 'R';
                can_write(game_mode);
                game = 0; // Spille spillet?
                int sec = 0;
                while(game){
                    _delay_ms(1000);
                    sec++;
                    oled_clear();
                    oled_print((char*)(sec));
                    if(mcp2515_check_bit(MCP_CANINTF,0)){
                        game = 0;
                        mcp2515_bit_modify(0b00000011,MCP_CANINTF,0b00000000);
                    }
                
                update_leaderboard(sec);
                current_menu_element = leaderboard;
                }
            
            }
            else if(&current_menu_element == &expert){
                game_mode.data[0] = 'E';
                int sec = 0;
                can_write(game_mode);
                game = 0; // spille spillet?
                while(game){
                    _delay_ms(1000);
                    sec++;
                    oled_clear();
                    oled_print((char*)(sec));
                    if(mcp2515_check_bit(MCP_CANINTF,0)){
                        game = 0;
                        mcp2515_bit_modify(0b00000011,MCP_CANINTF,0b00000000);
                    }
                }
                update_leaderboard(sec);
                current_menu_element = leaderboard;
            }
            oled_clear();
            oled_print_node_and_children(current_menu_element,current_pos);
            //while(joystick_get_direction()!= NEUTRAL){
            while(joystick_get_button_status()){
                _delay_ms(50);}

            }
    
        //if((joystick_get_direction() == LEFT) &&(current_menu_element.parent != NULL)){
        if(slider_get_left_button_status() && slider_get_right_button_status()){
            oled_clear();
            current_menu_element = *current_menu_element.parent;
            current_pos = 0;
            oled_print_node_and_children(current_menu_element,current_pos);
            //while(joystick_get_direction()!= NEUTRAL){
            while(slider_get_left_button_status() && slider_get_right_button_status()){
                _delay_ms(50);}
        }
    }

    //oled_clear();

    //oled_print("menu exit\n\n\n\n\n\n\n");
/*

void game_fsm(gamemode mode){
    switch(mode){    oled_print_node_and_children(main_menu,1);
    
        case ROOKIE:
            int game_score = playgame_rookie();
            update_leaderboard(game_score);
            break;
        case EXPERT:
            int game_score = playgame_expert();
            update_leaderboard(game_score);
            break;
        case leaderboard:

            break;
        case 
    }*/
}

