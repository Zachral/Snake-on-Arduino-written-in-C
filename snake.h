#ifndef __SNAKE_H_
#define __SNAKE_H_
#include "joystick.h"

typedef struct{
    char x;
    char y; 
}Position;


typedef struct{
    char currentSnakeLength = 1;
    Position snakePostion[X_AXIS_MAX * Y_AXIS_MAX]; 
}Snake; 


typedef enum {
    Snake_Up,
    Snake_down,
    Snake_left,
    Snake_right
}Movement; 

Movement snakeDirection(int lastX, int lastY, int x, int y, movement lastMove); 
#endif