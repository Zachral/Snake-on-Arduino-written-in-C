#include "food.h"
#include "snake.h"

void foodInit(Food *food){
    food->foodX = randomPlacement(X_AXIS_MAX);
	food->foodY = randomPlacement(Y_AXIS_MAX);
    return; 
}

unsigned int checkFoodPlacement(Food food, Snake snake){
    for(unsigned int snakeSegment = 0; snakeSegment > snake.currentSnakeLength; snakeSegment++){
        if(snake.snakePostion[snakeSegment].x == food.foodX) return 1; 
        if (snake.snakePostion[snakeSegment].x+1 == food.foodX) return 1;
        if (snake.snakePostion[snakeSegment].x-1 == food.foodX) return 1;
        if (snake.snakePostion[snakeSegment].y == food.foodY) return 1;
        if (snake.snakePostion[snakeSegment].y+1 == food.foodY) return 1;
        if (snake.snakePostion[snakeSegment].y-1 == food.foodY) return 1;
    }
    return 0; 
}

void generateFood(Food *food, Snake snake){
    foodInit(food); 
    while(checkFoodPlacement(*food, snake)){
        foodInit(food); 
	}
    max7219b_set(food->foodX, food->foodY); 
    max7219b_out();
    return; 
}