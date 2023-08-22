#include "text.h"
#include "joystick.h"
#include "max72xx.h"
#include <util/delay.h>

#define BIT_CHECK(a,b) (!!((a) & (1ULL<<(b)))) 


uint8_t displayLetter(uint8_t *letter, uint8_t letterSpace){
    uint8_t counter = letterSpace;
    for(uint8_t row = 0; row < 8; row++){ 
        uint8_t tempRow = letter[row];
        for(uint8_t column = 0; column < 8; column++){
            if(BIT_CHECK(tempRow, column)){
                counter = row; 
                 int8_t tempColumn = 8 - column;
                 if((column + letterSpace) < 0)
                     tempColumn = X_AXIS_MAX + tempColumn;
                max7219b_set((tempColumn + letterSpace-2), row);
            }
        }
    }
    max7219b_out();
    return letterSpace + counter-1;  
    
}

void clearLedMatrix(uint8_t maxX, uint8_t maxY){
    for(uint8_t x = 0; x < maxX; x++){
        for(uint8_t y = 0; y < maxY; y++){
            max7219b_clr(x,y);
        }
    }
    max7219b_out();
    return; 
}