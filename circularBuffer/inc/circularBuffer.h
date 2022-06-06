#ifndef __CIRCULAR_BUFFER__
#define __CIRCULAR_BUFFER__

#include "memory.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct {
    uint8_t * items;
    uint8_t itemSize;
    uint8_t maxItemCount;
    uint8_t currentItemCount;
    uint8_t firstItemIndex;
    uint8_t firstFreeIndex;
} CircularBuffer_t;

CircularBuffer_t * cbuf_createBuffer(uint8_t maxItemCount, uint8_t itemSize);

// Returns true if the item was successfully added, false otherwise
bool cbuf_add(CircularBuffer_t * buffer, void * item);

// Returns true if the item was successfully retrieved, false otherwise
bool cbuf_get(CircularBuffer_t * buffer, void * returnBuffer);

bool cbuf_isFull(CircularBuffer_t * buffer);
bool cbuf_isEmpty(CircularBuffer_t * buffer);

#endif