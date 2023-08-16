#include "max72xx.h"
#include "analogRead.h"
#include "joystick.h"
#include <stdio.h>
#include <string.h>
#include <util/delay.h>
#include <time.h>
#include <stdlib.h>
#include <avr/iom169.h>  
#include "uart.h"
#include "randomPlacement.h"
#include "snake.h"

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
	srand(analogRead(SEL_PIN)); 
	int snakeX = randomPlacement(X_AXIS_MAX);
	int snakeY = randomPlacement(Y_AXIS_MAX);
	int foodX = randomPlacement(X_AXIS_MAX);
	int foodY = randomPlacement(Y_AXIS_MAX);
	while(snakeX == foodX && snakeY == foodY){
		foodX = randomPlacement(X_AXIS_MAX);
		foodY = randomPlacement(Y_AXIS_MAX);
	}
	int currentSnakeLenght = 0; 
	Movement lastMove; 


	printf("x = %d\n", snakeX);
	printf("y = %d\n", snakeY); 
	max7219b_set(snakeX, snakeY); 
	max7219b_set(foodX, foodY); 
	max7219b_out();


	while (1) {
		int lastX = snakeX; 
		int lastY = snakeY;

		if(lastMove == Snake_down) max7219b_clr(lastX, lastY-currentSnakeLenght-1);
		else if(lastMove == Snake_Up) max7219b_clr(lastX, lastY+currentSnakeLenght+1);
		else if(lastMove == Snake_right) max7219b_clr(lastX-currentSnakeLenght-1, lastY);
		else if(lastMove == Snake_left) max7219b_clr(lastX+currentSnakeLenght+1, lastY);
		
		int horz = analogRead(HORZ_PIN);
  		int vert = analogRead(VERT_PIN);
		snakeX = joystickXAxis(horz, snakeX); 
		snakeY = joystickYAxis(vert, snakeY); 


	 	//plots the snake on led-matrix
		max7219b_set(snakeX, snakeY);
		max7219b_out();
		_delay_ms(100);
		lastMove = snakeDirection(lastX, lastY, snakeX, snakeY, lastMove);
		// if currentMove != lastMove
			// initialize currentMove varible
			// **Write logic for when snake moves direction**
		// currentMove = lastMove; 	
		printf("last move : %d\n", (int)lastMove);
		if(snakeX == foodX && snakeY == foodY){
			while (snakeX == foodX && snakeY == foodY){
			foodX = randomPlacement(X_AXIS_MAX);
			foodY = randomPlacement(Y_AXIS_MAX);
			}
			max7219b_set(foodX, foodY); 
			max7219b_out();
			currentSnakeLenght++; 
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