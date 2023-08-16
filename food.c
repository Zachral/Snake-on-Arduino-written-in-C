#include "food.h"
#include "snake.h"

void foodInit(Food *food){
    food->foodX = randomPlacement(X_AXIS_MAX);
	food->foodY = randomPlacement(Y_AXIS_MAX);
    return; 
}

void generateFood(Food *food, Snake snake){
    while(snake.snakePostion[0].x == food->foodX && snake.snakePostion[0].y == food->foodY){
		food->foodX = randomPlacement(X_AXIS_MAX);
		food->foodY = randomPlacement(Y_AXIS_MAX);
	}
    max7219b_set(food->foodX, food->foodY); 
    return; 
}