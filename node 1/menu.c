#include "menu.h"


char* menu_score_string_update(){

    char first_place[8]; 
    char second_place[8];
    char third_place[8];

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
    strcat(string, "\n\n");

    return string;
    
}

void menu_oled_print_node_and_children(menu_element element, int elem_nr){ //Printing each menu screen

    oled_print_font(element.print, 8);
    int i = 0;
    oled_print("\n \n");

    while( element.children[i] != NULL){
        if((i == elem_nr) && (element.nr_children != -1)){ // Only the main menu and game mode select should have an arrow
            oled_print("->");
        }
        
        else if(element.nr_children >= 0){ //The last menu should not be affected
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
void menu_update_leaderboard(int score){

    int temp_leaderboard[3];
    if(score > LEADERBOARD[0]){
        
        temp_leaderboard[1] = LEADERBOARD[0];
        temp_leaderboard[2] = LEADERBOARD[1];
        temp_leaderboard[0] = score;
        
    }else if(score > LEADERBOARD[1]){
        temp_leaderboard[0]= LEADERBOARD[0];
        temp_leaderboard[2] = LEADERBOARD[1];
        temp_leaderboard[1] = score;
    }else if(score > LEADERBOARD[2]){
        temp_leaderboard[0] = LEADERBOARD[0];
        temp_leaderboard[1] = LEADERBOARD[1];
        temp_leaderboard[2] = score;
    }else{
        return;
    }
    for(int i = 0; i<3;i++){
        LEADERBOARD[i]= temp_leaderboard[i];
    }
}


char* menu_get_score_string(int sec){ //Combines char with int for easy oled-printing

    char seconds_string[5]; 

    char score_string[100];
    
    itoa(sec, seconds_string, 10);

    strcpy(score_string, "Score. ");
    strcat(score_string, seconds_string);

    return score_string;

}

void menu_run_intro(){ //Star wars intro + "ping pong game" screen

    char* star_wars_strings[25] = {"","","","","","","","A long time", "ago in", "a sanntidssal", "far", "far away...", "","","","","","","","",""};

    joystick_init();
    for(int i = 0; i < 13; i++){
        
        for(int j = 0; j < 7; j++){
        oled_print_font(star_wars_strings[j+i],8);
        oled_print("\n");
        }
        if (joystick_get_direction())
            _delay_ms(200);
        else
            _delay_ms(2000);
        
        oled_clear();
    }

    oled_clear();

        oled_print_font("Ping pong game\n",8);
        oled_print_font("\n \n press joystick \n to continue\n\n\n",5);
    while(!joystick_get_button_status()){
    }
    while(joystick_get_button_status()){
        ;
    }
    oled_clear;
}




void menu_run(){

    oled_clear();
    menu_run_intro();
    
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

    rookie.parent = &play_game;//game is over
    rookie.children[0] = NULL;
    rookie.print = "Rookie";

    expert.parent = &play_game;
    expert.print = "Expert";
    
    menu_element leaderboard;
    leaderboard.parent = &main_menu;
    leaderboard.children[0] = &highscore;
    leaderboard.nr_children = -1;
    leaderboard.print = "Leaderboard";


    int sec = 0;

    char* string = menu_score_string_update(); //Empty scoreboard
    char* score_string;

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
    credits_text.print = "Eilef  O.\nMartin S.\nAsgeir H.\nIn remembrance \nof heroic effort";

    main_menu.parent = NULL;
    main_menu.children[0] = &play_game;
    main_menu.children[1] =  &leaderboard;
    main_menu.children[2] = &credits;
    main_menu.print = "Main menu";
    main_menu.nr_children = 3;
    
    uint8_t current_pos = 0;
    oled_clear();
    menu_oled_print_node_and_children(main_menu,current_pos);

    menu_element current_menu_element = main_menu;
    
    uint8_t game = 0;

        while(1){
        printf("Direction:          %d\n\r", joystick_get_direction());
        printf(" Vidererføring\n\r");
        message game_mode;
        game_mode.ID = 2;
        game_mode.length = 6;
        game_mode.data[0] = 1;
        /* Activated when joystick goes up and its not the upper element and not the credits */
        if(joystick_get_direction() == UP && current_pos != 0 && current_menu_element.nr_children != -1){ //Increments menu up
            
            oled_clear();
            current_pos--;
            menu_oled_print_node_and_children(current_menu_element,current_pos % current_menu_element.nr_children);

            while(joystick_get_direction()){ //waiting for the joystick to return to neutral
                _delay_ms(50); // waiting in case the joystick bounces
                }
        }
        /* Activated when the joystick goes down and its not the lowest element and not the credits*/
        if(joystick_get_direction() == DOWN && current_pos != current_menu_element.nr_children - 1 && current_menu_element.nr_children != 1){ // decrements the menu down
            oled_clear();
            current_pos++;
            
            menu_oled_print_node_and_children(current_menu_element,current_pos%current_menu_element.nr_children);

            while(joystick_get_direction()){ //Waiting for the joystick to return to neutral
                _delay_ms(50); //waiting in case the joystick bounces back
                }
        }
        sec = 0;
 
        /* Activated when joystick goes right and there are no further rights to go*/
        if((joystick_get_direction() == RIGHT) && ((current_menu_element.nr_children != -1))){ //selects a meny option
            //game is over
            oled_clear();
            current_menu_element = *current_menu_element.children[current_pos];
            current_pos = 0;
            menu_oled_print_node_and_children(main_menu,1);

            if(current_menu_element.print == "Rookie" || current_menu_element.print == "Expert"){
                
                if(current_menu_element.print == "Rookie"){
                    game_mode.data[0] = 'R';
                    oled_clear();
                    oled_print("Playing rookie \n mode \n\n\n\n\n\n");
                }
                if(current_menu_element.print == "Expert"){
                    game_mode.data[0] = 'E';
                    oled_clear();
                    oled_print("Playing expert \nmode \n\n\n\n\n\n");
                }
                can_write(game_mode); //Sending which game mode to play in node 2
                game = 1;
                while(game){ //Sending joystick and slider info, updating scorescreen and waiting for signal from node 2 to teminate game
                    can_send_actuator_signals();
                    sec+=2;

                    score_string = menu_get_score_string(sec);
                    if(sec % 100 == 0){
                        oled_clear();
                        oled_print(score_string);
                        oled_print("\n\n\n\n\n\n\n");
                    }

                    if(can_check_recieved_flag()){
                        game = 0;
                        game_mode.data[0] = 0; //sending game is over
                        can_write(game_mode);
                        can_read(); //To remove the interrupt flag 
                    }
                }

                menu_update_leaderboard(sec);
            
                char* string = menu_score_string_update();

                highscore.print = string;
                current_menu_element = leaderboard;
            
            }

                
            oled_clear();
            menu_oled_print_node_and_children(current_menu_element,current_pos);
            while(joystick_get_direction()){ //waiting for the joystick to remain neutral
                _delay_ms(50);
            }
        }
        
        // Activates when the left slider button is touched and its not the main menu
        if((slider_get_left_button_status()) && (current_menu_element.parent != NULL)){ // goes back one menu screen 
            oled_clear();
            current_menu_element = *current_menu_element.parent;
            current_pos = 0;
            menu_oled_print_node_and_children(current_menu_element,current_pos);
            while(slider_get_left_button_status()){
                _delay_ms(50);
            }
        }
    }
}