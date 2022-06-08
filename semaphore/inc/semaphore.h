#ifndef __SEMAPHORE__
#define __SEMAPHORE__

#include "memory.h"
#include "stdbool.h"
#include "stdint.h"

typedef struct {
    uint8_t maxValue;
    uint8_t currentValue;
} Semaphore_t;

Semaphore_t * smph_createSemaphore(uint8_t maxValue);

// Returns true if semaphore acquisition is successful, false otherwise
bool smph_take(Semaphore_t * semaphore);

// Returns true if semaphore release is successful, false otherwise
bool smph_give(Semaphore_t * semaphore);

#endif