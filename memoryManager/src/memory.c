#include "memory.h"

extern uint32_t heapStart;
extern uint32_t heapEnd;
extern uint32_t heapSize;

void memMang_initHeap(void) {
    MemoryBlockHeader_t * blockHeader = (MemoryBlockHeader_t *)&heapStart;
    blockHeader->isAllocated = 0;
    blockHeader->size = (uint32_t)(&heapEnd - &heapStart - sizeof(MemoryBlockHeader_t));
    MemoryBlockHeader_t * blockFooter = (MemoryBlockHeader_t *)((pointerSize_t)blockHeader + blockHeader->size - sizeof(MemoryBlockHeader_t));
    *blockFooter = *blockHeader;
    MemoryBlockHeader_t * finishingBlock = blockFooter + 1;
    finishingBlock->isAllocated = 0;
    finishingBlock->size = 0;
}

void * memMang_malloc(uint32_t requestedSize) {
    MemoryBlockHeader_t * blockHeader = (MemoryBlockHeader_t *)&heapStart;
    uint32_t requiredSize = requestedSize + 2 * sizeof(MemoryBlockHeader_t);
    while (blockHeader->size) {
        if (blockHeader->isAllocated || blockHeader->size < requiredSize) {
            blockHeader = (MemoryBlockHeader_t *)((pointerSize_t)blockHeader + blockHeader->size);
        } else {
            blockHeader->isAllocated = 1;
            if (blockHeader->size > requiredSize + 2 * sizeof(MemoryBlockHeader_t)) {
                pointerSize_t oldSize = blockHeader->size;
                blockHeader->size = requiredSize;

                MemoryBlockHeader_t * nextHeader = (MemoryBlockHeader_t *)((pointerSize_t)blockHeader + blockHeader->size);
                nextHeader->size = oldSize - blockHeader->size;
                nextHeader->isAllocated = 0;
                MemoryBlockHeader_t * nextFooter = (MemoryBlockHeader_t *)((pointerSize_t)nextHeader + nextHeader->size - sizeof(MemoryBlockHeader_t));
                *nextFooter = *nextHeader;
                uint32_t i = 0;
            }
            MemoryBlockHeader_t * blockFooter = (MemoryBlockHeader_t *)((pointerSize_t)blockHeader + blockHeader->size - sizeof(MemoryBlockHeader_t));
            *blockFooter = *blockHeader;

            return blockHeader + 1;
        }
    }
    return (void *)-1;
}

void memMang_free(void * memoryAddress) {
    MemoryBlockHeader_t * blockHeader = (MemoryBlockHeader_t *)memoryAddress - 1;
    blockHeader->isAllocated = 0;
    MemoryBlockHeader_t * blockFooter = (MemoryBlockHeader_t *)((pointerSize_t)blockHeader + blockHeader->size - sizeof(MemoryBlockHeader_t));
    blockFooter->isAllocated = 0;

    if (blockHeader != (MemoryBlockHeader_t *)&heapStart) {
        MemoryBlockHeader_t * prevFooter = blockHeader - 1;
        if (!prevFooter->isAllocated) {
            blockHeader = blockHeader - prevFooter->size;
            blockHeader->size += blockFooter->size;
            *blockFooter = *blockHeader;
        }
    }

    if (blockFooter != (MemoryBlockHeader_t *)&heapEnd - 1) {
        MemoryBlockHeader_t * nextHeader = blockFooter + 1;
        if (!nextHeader->isAllocated) {
            blockHeader->size += nextHeader->size;
            blockFooter = nextHeader + nextHeader->size - 1;
            *blockFooter = *blockHeader;
        }
    }
}