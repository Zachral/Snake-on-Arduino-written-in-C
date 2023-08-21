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
#include "millis.h"
#include <avr/interrupt.h>

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
	
	millis_init();
	sei(); 
	init_serial();
	max7219_init();
	
}

//// https://wokwi.com/projects/296234816685212169


int main()
{
	hardwareInit(); 
	Snake snake; 	
	Movement currentMove = snakeInit(&snake, currentMove); 
	Food food; 
	foodInit(&food); 
	generateFood(&food, snake); 
	Movement lastMove; 
	max7219b_out();
	int horizontal;
  	int vertical;
	volatile millis_t millisecondsSinceLastSnakeMove = 0; 
	printf("current move = %d", currentMove); 
	
	while (1) {
		if(millis_get() - millisecondsSinceLastSnakeMove > 500){
			automaticSnakeMovement(&snake, currentMove);
			millisecondsSinceLastSnakeMove = millis_get();
			printf("Millis X = %d, Millis Y = %d\n", snake.snakePostion[0].x, snake.snakePostion[0].y);
		}
		horizontal = analogRead(HORZ_PIN);
  		vertical = analogRead(VERT_PIN);
		_delay_ms(50); 
		if(snakeHasMoved(horizontal,vertical)){
			millisecondsSinceLastSnakeMove = millis_get();
		}
		//Skriv om som funktion? dels en för for-loop och en för att kolla om snake flyttat, return 0?
		if(snake.currentSnakeLength > 1){
			if(snakeHasMoved(horizontal, vertical)){
	 		//plots the snake on led-matrix
				for(char segment = snake.currentSnakeLength; segment > 0; segment--){
              		snake.snakePostion[segment].x = snake.snakePostion[segment-1].x;
              		snake.snakePostion[segment].y = snake.snakePostion[segment-1].y; 
			  		max7219b_set(snake.snakePostion[segment].x, snake.snakePostion[segment].y);
       			} 
			}
		}
		snake.snakePostion[0].x = joystickXAxis(horizontal, snake.snakePostion[0].x); 
		snake.snakePostion[0].y = joystickYAxis(vertical, snake.snakePostion[0].y); 
		max7219b_set(snake.snakePostion[0].x, snake.snakePostion[0].y); 
		printf("snake X = %d, snake Y = %d\n", snake.snakePostion[0].x, snake.snakePostion[0].y);
		max7219b_out();
		clearSnakeTail(snake); 
		
		if(snake.snakePostion[0].x == food.foodX && snake.snakePostion[0].y == food.foodY){
			snakeGrow(&snake); 
			generateFood(&food, snake); 
		}
	}
	return 0;
}