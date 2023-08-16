#include "snake.h"
#include <time.h>
#include <stdlib.h>

char randomPlacement(randomMax){
    return (rand() % randomMax);
}


void snakeInit(){

};


Movement snakeDirection(int lastX, int lastY, int snakeX, int snakeY, Movement lastMove){
       if(snakeX > lastX) return Snake_right;
       else if(snakeX < lastX) return Snake_left; 
       else if(snakeY > lastY) return Snake_down;
       else if(snakeY < lastY) return Snake_Up; 
       else return lastMove; 
};


