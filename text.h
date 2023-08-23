#ifndef __TEXT_H_
#define __TEXT_H_
#include <stdint.h>

typedef struct{
    uint8_t letterG[8];
    uint8_t letterA[8];
    uint8_t letterM[8];
    uint8_t letterE[8];
} GAME; 

void printLetterToLED(uint8_t array[4][8]);
//uint8_t displayLetter(uint8_t *letter, uint8_t letterSpace);
void clearLedMatrix(uint8_t maxX, uint8_t maxY);
#endif