#ifndef __TEXT_H_
#define __TEXT_H_
#include <stdint.h>

typedef struct{
    uint8_t letterG[8];
    uint8_t letterA[8];
    uint8_t letterM[8];
    uint8_t letterE[8];
} GAME; 

typedef struct{
    uint8_t letterW[8];
    uint8_t letterI[8];
    uint8_t letterN[8];
}WIN;

typedef struct{
    uint8_t letterE[8];
    uint8_t letterD[8];
}END;

uint8_t printLetterToLED(uint8_t *letter, uint8_t letterSpace);
void clearLedMatrix(uint8_t maxX, uint8_t maxY);
#endif