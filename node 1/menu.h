#ifndef _MENU_
#define _MENU_

#include "oled.h"
#include "joystick.h"
#include <util/delay.h>

typedef enum gamemode{
    rookie;
    expert;    
} gamemode;

void menu();

typedef struct menu_element {
    struct menu_element* parent;
    struct menu_element* children[4];
    char* print;
    int nr_children;
}; menu_element;



#endif