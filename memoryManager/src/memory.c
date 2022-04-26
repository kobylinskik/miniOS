#include "memory.h"

extern uint32_t heapStart;
extern uint32_t heapEnd;
extern uint32_t heapSize;

void initHeap() {
    memoryBlock_t * blockHeader = (memoryBlock_t *)&heapStart;
    blockHeader->isAllocated = 0;
    blockHeader->size = (uint32_t)&heapSize;
}

void * allocateMemory(uint32_t memorySize) {
    memoryBlock_t * blockHeader = (memoryBlock_t *)&heapStart;
    while ((uint32_t)blockHeader < (uint32_t)&heapEnd) {
        if (blockHeader->isAllocated || blockHeader->size < memorySize + 1) {
            blockHeader = blockHeader + blockHeader->size;
        } else {
            uint32_t oldSize = blockHeader->size;
            blockHeader->size = memorySize + 1;
            blockHeader->isAllocated = 1;
            memoryBlock_t * nextHeader = blockHeader + memorySize + 1;
            nextHeader->size = oldSize - blockHeader->size;
            nextHeader->isAllocated = 0;
            return blockHeader + 1;
        }
    }
}

void freeMemory(void * memoryAddress) {
    memoryBlock_t * memoryBlock = (memoryBlock_t *)memoryAddress - 1;
    memoryBlock->isAllocated = 0;
    (memoryBlock + memoryBlock->size - 1)->isAllocated = 0;
}