#include "semaphore.h"

Semaphore_t * smph_createSemaphore(uint8_t maxValue) {
    Semaphore_t * semaphore = memMang_malloc(sizeof(Semaphore_t));
    semaphore->maxValue = maxValue;
    semaphore->currentValue = 0;
    return semaphore;
}

// Returns true if mutex acquisition is successful, false otherwise
bool smph_take(Semaphore_t * semaphore) {
    if (semaphore->currentValue == semaphore->maxValue) {
        return false;
    }
    semaphore->currentValue++;
    return true;
}

// Returns true if mutex release is successful, false otherwise
bool smph_give(Semaphore_t * semaphore) {
    if (!semaphore->currentValue) {
        return false;
    }
    semaphore->currentValue--;
    return true;
}