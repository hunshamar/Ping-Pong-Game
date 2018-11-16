#include "motor_controller.h"
#include "pi.h"
#include "solenoid.h"





typedef enum MODE{
    MODE_SPEED = 0,
    MODE_POSITION = 1
}MODE;


void game_play(MODE m);