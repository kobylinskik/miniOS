#ifndef __MEMORY_MANAGER__
#define __MEMORY_MANAGER__

#include <stdint.h>

typedef uint32_t pointerSize_t;

typedef struct {
    pointerSize_t isAllocated : 1;
    pointerSize_t size : 31;
} MemoryBlockHeader_t;

void memMang_initHeap(void);
void * memMang_malloc(uint32_t requestedSize);
void memMang_free(void * memoryAddress);

#endif