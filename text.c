#include "text.h"
#include "joystick.h"
#include "max72xx.h"
#include <util/delay.h>

#define BIT_CHECK(a,b) (!!((a) & (1ULL<<(b)))) 


 void printLetterToLED(uint8_t array[4][8]){
    for(uint8_t element = 0; element < sizeof array[0]; element++){
        printf("Element %d\n", element);
		uint8_t currentCol = 0; 
        for(uint8_t row = 0; row < 8; row++){
			currentCol = element * 8; // Här börjar denna bokstav
                for(uint8_t bit = 7; bit >= 0 && bit <=7; bit--){
					currentCol++;	
                    if(BIT_CHECK(array[element][row],bit)){
						if (element == 0) max7219b_set(currentCol-2,row);
						else if(element == 1) max7219b_set(currentCol-5,row);
						else if(element == 2) max7219b_set(currentCol -9,row); 
						else max7219b_set(currentCol -12,row);	
					}
				}
        }
		max7219b_out();
    }
    return; 
 } 


// uint8_t displayLetter(uint8_t *letter, uint8_t letterSpace){
//     uint8_t counter = letterSpace;
//     for(uint8_t row = 0; row < 8; row++){ 
//         uint8_t tempRow = letter[row];
//         for(uint8_t column = 0; column < 8; column++){
//             if(BIT_CHECK(tempRow, column)){
//                 counter = row; 
//                  int8_t tempColumn = 8 - column;
//                  if((column + letterSpace) < 0)
//                      tempColumn = X_AXIS_MAX + tempColumn;
//                 max7219b_set((tempColumn + letterSpace-2), row);
//             }
//         }
//     }
//     max7219b_out();
//     return letterSpace + counter-1;  
    
// }

void clearLedMatrix(uint8_t maxX, uint8_t maxY){
    for(uint8_t x = 0; x < maxX; x++){
        for(uint8_t y = 0; y < maxY; y++){
            max7219b_clr(x,y);
        }
    }
    max7219b_out();
    return; 
}