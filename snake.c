#include "snake.h"
#include <time.h>
#include <stdlib.h>

char randomPlacement(randomMax){
    return (rand() % randomMax);
}


void snakeInit(Snake *snake){
       srand(analogRead(2)); 
	snake->snakePostion[0].x = randomPlacement(X_AXIS_MAX);
	snake->snakePostion[0].y = randomPlacement(Y_AXIS_MAX);
	snake->currentSnakeLength = 1; 
};


Movement snakeDirection(int lastX, int lastY, int snakeX, int snakeY, Movement lastMove){
       if(snakeX > lastX) return Snake_right;
       else if(snakeX < lastX) return Snake_left; 
       else if(snakeY > lastY) return Snake_down;
       else if(snakeY < lastY) return Snake_Up; 
       else return lastMove; 
};


