#include "snake.h"
#include "max72xx.h"
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
       max7219b_set(snake->snakePostion[0].x, snake->snakePostion[0].y); 
       return; 
};

// void plotSnakeOnLed(Snake *snake){
// 	if ((snake->snakePostion[0].x != snake->snakePostion[1].x) || (snake->snakePostion[0].y != snake->snakePostion[1].y)){
// 		for(char i = snake->currentSnakeLength; i > 0; i--){
//               	snake->snakePostion[i].x = snake->snakePostion[i-1].x;
//               	snake->snakePostion[i].y = snake->snakePostion[i-1].y; 
// 			max7219b_set(snake->snakePostion[i].x, snake->snakePostion[i].y);
//        		} 
//        }
//        return; 
// }

void snakeGrow(Snake *snake){
       snake->currentSnakeLength++;
       // max7219b_set(snake->snakePostion[snake->currentSnakeLength-1].x, snake->snakePostion[snake->currentSnakeLength-1].y);
       // max7219b_out(); 
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

Movement snakeDirection(int lastX, int lastY, int snakeX, int snakeY, Movement lastMove){
       if(snakeX > lastX) return Snake_right;
       else if(snakeX < lastX) return Snake_left; 
       else if(snakeY > lastY) return Snake_down;
       else if(snakeY < lastY) return Snake_Up; 
       else return lastMove; 
};


