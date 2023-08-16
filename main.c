#include "max72xx.h"
#include "analogRead.h"
#include "joystick.h"
#include <stdio.h>
#include <string.h>
#include <util/delay.h>
#include <time.h>
#include <stdlib.h> 
#include "uart.h"
#include "snake.h"
#include "food.h"

#define VERT_PIN 0
#define HORZ_PIN 1
#define SEL_PIN  2

#define BIT_SET(a, b) ((a) |= (1ULL << (b)))
#define BIT_CLEAR(a,b) ((a) &= ~(1ULL<<(b)))
#define BIT_FLIP(a,b) ((a) ^= (1ULL<<(b)))
#define BIT_CHECK(a,b) (!!((a) & (1ULL<<(b)))) 

#define BUTTON_IS_CLICKED(PINB,BUTTON_PIN) !BIT_CHECK(PINB,BUTTON_PIN)

void hardwareInit(){
	BIT_CLEAR(DDRC,VERT_PIN);
	BIT_CLEAR(DDRC,HORZ_PIN);

	//Sätt till INPUT_PULLUP
    BIT_CLEAR(DDRD,SEL_PIN); // INPUT MODE
    BIT_SET(PORTD,SEL_PIN); 

	init_serial();
	max7219_init();
}

//// https://wokwi.com/projects/296234816685212169


int main()
{
	hardwareInit(); 
	Snake snake; 	
	snakeInit(&snake); 
	Food food; 
	foodInit(&food); 
	generateFood(&food, snake); 
	Movement lastMove; 
	printf("x = %d\n", snake.snakePostion[0].x);
	printf("y = %d\n", snake.snakePostion[0].y); 
	max7219b_out();


	while (1) {
		int lastX = snake.snakePostion[0].x; 
		int lastY = snake.snakePostion[0].y;

		// if(lastMove == Snake_down) max7219b_clr(lastX, lastY-currentSnakeLenght-1);
		// else if(lastMove == Snake_Up) max7219b_clr(lastX, lastY+currentSnakeLenght+1);
		// else if(lastMove == Snake_right) max7219b_clr(lastX-currentSnakeLenght-1, lastY);
		// else if(lastMove == Snake_left) max7219b_clr(lastX+currentSnakeLenght+1, lastY);
		
		int horz = analogRead(HORZ_PIN);
  		int vert = analogRead(VERT_PIN);
		snake.snakePostion[0].x = joystickXAxis(horz, snake.snakePostion[0].x); 
		snake.snakePostion[0].y = joystickYAxis(vert, snake.snakePostion[0].y); 


	 	//plots the snake on led-matrix
		max7219b_set(snake.snakePostion[0].x, snake.snakePostion[0].y);
		max7219b_out();
		_delay_ms(100);
		lastMove = snakeDirection(lastX, lastY, snake.snakePostion[0].x, snake.snakePostion[0].y, lastMove);
		// if currentMove != lastMove
			// initialize currentMove varible
			// **Write logic for when snake moves direction**
		// currentMove = lastMove; 	
		//printf("last move : %d\n", (int)lastMove);
		if( snake.snakePostion[0].x == food.foodX && snake.snakePostion[0].y == food.foodY){
			generateFood(&food, snake); 
			max7219b_out();
			snake.currentSnakeLength++; 
		}
		
		
		
		//Snake moving constantly left. 
		// for(int i = 0; i < 16;i++){
		// 	printf("%d\n", i);
		// 	max7219b_set(i, y);
		// 	max7219b_out();
		// 		_delay_ms(1000);
		// }
	}
	return 0;
}