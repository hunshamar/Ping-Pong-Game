#ifndef _MENU_
#define _MENU_

#include "oled.h"
#include "joystick.h"
#include <util/delay.h>
#include "can_driver.h"
#include "stdlib.h"
#include <string.h>





int LEADERBOARD[3];
typedef enum gamemode{
    rookie1,
    expert1    
} gamemode;

void menu();
void update_leaderboard(int score);

typedef struct menu_element {
    struct menu_element* parent;
    struct menu_element* children[5];
    char* print;
    int nr_children;
} menu_element;


void oled_print_node_and_children(menu_element element, int elem_nr);

char* menu_update_leaderboard();


char* menu_score_string_update();

#endif