#ifndef _FOOD_H_
#define _FOOD_H_
#include "snake.h"

typedef struct{
    char foodX;
    char foodY; 
}Food; 

void foodInit(Food *food); 
void generateFood(Food *food, Snake snake); 
#endif