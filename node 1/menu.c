#include "menu.h"

void visual_menu(){

    char* str1 = "\n->Play game\n  Leaderboard\n  Credits\n \n \n \n";
    char* str2 = "\n  Play game\n->Leaderboard\n  Credits\n \n \n \n";
    char* str3 = "\n  Play game\n  Leaderboard\n->Credits\n \n \n \n ";
    char* sub_str1_1 = "\n-> Rookie \n Expert\n \n \n \n \n \n";
    char* sub_str1_2 = "\nRookie \n ->Expert\n \n \n \n \n \n";
    int Leaderboard = [0,0,0,0,0];
    char* Credits = "\n Eilef Olsen Osvik\n Martin Aalby Svalesen \n Asgeir Hunshamar \n In remembrance of heroic effort. \n Copyright 2018 \n \n";


    char* menu[3] = {str1, str2, str3};
    char* sub_menu_1[2] = {sub_str1_2,sub_str1_1};

    int pos = 0;
    oled_clear();
    oled_print(menu[pos]);

    joystick_init();

    menu_element main_menu;
    
    menu_element play_game;
    play_game.parent = main_menu;
    play_game.children[0] = gamemode;
    play_game.nr_children = 1;
    play_game.print = "Play game\n";

    menu_element game_mode;
    game_mode.parent = play_game;
    game_mode.children[0] = rookie;
    game_mode.children[1] = expert;
    game_mode.nr_children = 2;
    game_mode.print = "Select gamemode\n";

    menu_element rookie;
    rookie.parent = play_game;
    rookie.children = NULL;
    rookie.print = "Rookie\n";

    menu_element expert;
    expert.parent = play_game;
    expert.print = "Expert\n";

    menu_element leaderboard;
    leaderboard.parent = main_menu;
    leaderboard.children = NULL;
    leaderboard.nr_children = 0;
    leaderboard.print = "Leaderboard\n";

    menu_element credits;
    credits.parent = main_menu;
    credits.children = NULL;
    credits.nr_children = 0;
    credits.print = "Credits\n";

    menu_element credits_text;
    credits_text.parent = credits;
    credits_text.children = NULL;
    credits_text.nr_children = 0;
    credits_text.print = "\n Eilef Olsen Osvik\n Martin Aalby Svalesen \n Asgeir Hunshamar \n In remembrance of heroic effort. \n Copyright 2018 \n \n";

    
    main_menu.parent = NULL;
    main_menu.children[0] = play_game;
    main_menu.children[1] =  leaderboard;
    main_menu.children[2] = credits;
    main_menu.print = "\n Main menu\n";
    main_menu.nr_children = 3;

    oled_print_node_and_children(main_menu,elem_nr);

    menu_element current_menu_element = main_menu;
    int current_pos = 0;
    int seconds;
    int game = 0;

    while(1){
        int x = joystick_get_x();
        int y = joystick_get_y();

        message game_mode;
        game_mode.ID = 2;
        game_mode.length = 6;
        game_mode.data[0] = 1;

        if(joystick_get_direction() == UP){
            oled_clear();
            current_pos--;
            oled_print_node_and_children(current_menu_element,current_pos%current_menu_element.nr_children);
            while(joystick_get_direction()!= NEUTRAL){
                _delay_ms(50);}
        }

        if(joystick_get_direction() == DOWN){
            oled_clear();
            current_pos++;
            oled_print_node_and_children(current_menu_element,current_pos%current_menu_element.nr_children);
            while(joystick_get_direction()!= NEUTRAL){
                _delay_ms(50);}
        }

        if((joystick_get_direction() == RIGHT) && ((current_menu_element.children != NULL))){
                oled_clear();
                current_menu_element = current_menu_element.children[current_pos];
                current_pos = 0;

                if(current_menu_element = rookie){
                    game_mode.data[0] = "Rookie";
                    sec = 0;
                    can_write(game_mode);
                    game = TRUE;
                    while(game){
                        _delay_ms(1000);
                        sec++;
                        oled_clear();
                        oled_print(sec);
                        if(mcp2515_check_bit(MCP_CANINTF,0)){
                            game = FALSE;
                            mcp2515_bit_modify(0b00000011,MCP_CANINTF,0b00000000);
                        }
                    }
                    update_leaderboard(sec);
                    current_menu_element = leaderboard;

                }
                else if(current_menu_element = expert){
                    game_mode.data[0] = "Expert";
                    sec = 0;
                    can_write(game_mode);
                    while(game){
                        _delay_ms(1000);
                        sec++;
                        oled_clear();
                        oled_print(sec);
                        if(mcp2515_check_bit(MCP_CANINTF,0)){
                            game = FALSE;
                            mcp2515_bit_modify(0b00000011,MCP_CANINTF,0b00000000);
                        }
                    }
                    update_leaderboard(sec);
                    current_menu_element = leaderboard;
                }

                oled_print_node_and_children(current_menu_element,current_pos);
                while(joystick_get_direction()!= NEUTRAL){
                    _delay_ms(50);}
            }
        if((joystick_get_direction() == LEFT) &&(current_menu_element.parent != NULL)){
            oled_clear();
            current_menu_element = current_menu_element.parent;
            current_pos = 0;
            oled_print_node_and_children(current_menu_element,current_pos);
            while(joystick_get_direction()!= NEUTRAL){
                _delay_ms(50);}
        }
    }










    while(!slider_get_right_button_status()){
        int x = joystick_get_x();
        int y = joystick_get_y();

        //oled_init();
        if(joystick_get_direction() == UP){
            printf("%d\n\r", pos%3);
            pos += 1;
            oled_clear();
            oled_print(menu[pos%3]);
            while(joystick_get_direction()!= NEUTRAL){
                _delay_ms(50);
            }
        }
        else if (joystick_get_direction() == DOWN){
            printf("%d\n\r", pos%3);
            pos -= 1;
            if(pos == -1){
                pos = 2;
            }
            oled_clear();
            oled_print(menu[pos%3]);
            while(joystick_get_direction()!= NEUTRAL){
                _delay_ms(50);
            }
        }

        if(joystick_get_direction() == RIGHT){
            oled_clear();
            oled_print(sub_menu[pos%3]);
            while(!joystick_get_button_status()){

            }
            oled_clear();
            oled_print(menu[pos%3]);
        }
        

        
    }

    //oled_clear();

    //oled_print("menu exit\n\n\n\n\n\n\n");

void update_leaderboard(int score){
    temp_leaderboard[5];
    int placing_index;
    for (i=0;i<5;i++){
        if(Leaderboard[i]<score){
            placing_index = i;
        }
        break;
    for (i = 0; i < placing_index;i++){
        temp_leaderboard[i]=Leaderboard[i];
    }
    temp_leaderboard[placing_index]=score;
    for (i = placing_index+1;i<4;i++){
        temp_leaderboard[i]=Leaderboard[i+1];
    }
    Leaderboard = temp_leaderboard;
}

void game_fsm(gamemode mode){
    switch(mode){
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
    }
}

