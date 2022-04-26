#ifndef __MEMORY_MANAGER__
#define __MEMORY_MANAGER__

#include <stdint.h>

typedef struct {
    uint32_t isAllocated : 1;
    uint32_t size : 31;
} memoryBlock_t;

void initHeap();
void * allocateMemory(uint32_t memorySize);
void freeMemory(void * memoryAddress);

#endif