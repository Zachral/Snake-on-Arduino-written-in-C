#include "snake.h"
#include "max72xx.h"
#include <time.h>
#include <stdlib.h>

#define RANDOMIZER_PIN  2

char randomPlacement(randomMax){
    return (rand() % randomMax);
}


Movement snakeInit(Snake *snake, Movement currentMove){
       srand(analogRead(RANDOMIZER_PIN)); 
	snake->snakePostion[0].x = randomPlacement(X_AXIS_MAX);
	snake->snakePostion[0].y = randomPlacement(Y_AXIS_MAX);
	snake->currentSnakeLength = 1; 
       max7219b_set(snake->snakePostion[0].x, snake->snakePostion[0].y);
       return currentMove = (snake->snakePostion[0].x >= 8) ? Snake_left : Snake_right;
     
};

void automaticSnakeMovement(Snake *snake, Movement currentMove){
       if(currentMove == Snake_right) snake->snakePostion[0].x = snake->snakePostion[0].x+1;
		else if(currentMove == Snake_left) snake->snakePostion[0].x = snake->snakePostion[0].x-1;
		else if(currentMove == Snake_Up) snake->snakePostion[0].y = snake->snakePostion[0].y-1;
		else if(currentMove == Snake_down) snake->snakePostion[0].y = snake->snakePostion[0].y+1;
		max7219b_set(snake->snakePostion[0].x, snake->snakePostion[0].y); 
		max7219b_out();
       return; 
}

void snakeGrow(Snake *snake){
       snake->currentSnakeLength++;
       return; 
}

void clearSnakeTail(Snake snake){
       if(snake.currentSnakeLength > 1){ 
              max7219b_clr(snake.snakePostion[snake.currentSnakeLength].x, snake.snakePostion[snake.currentSnakeLength].y);
       }else{ 
              max7219b_clr(snake.snakePostion[snake.currentSnakeLength-1].x, snake.snakePostion[snake.currentSnakeLength-1].y);
       }
       return; 
} 

unsigned int snakeHasMoved(int horizontal, int vertical, Movement *currentMove){
       if(horizontal > 700){
       *currentMove = Snake_left; 
       return 1;
       }
       if(horizontal < 300) {
       *currentMove = Snake_right; 
       return 1;
       } 
       if(vertical > 700) {
       *currentMove = Snake_Up; 
       return 1;
       }
       if(vertical < 300) {
       *currentMove = Snake_down; 
       return 1;
       }; 
       return 0; 
}


