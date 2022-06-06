#include "circularBuffer.h"

CircularBuffer_t * cbuf_createBuffer(uint8_t maxItemCount, uint8_t itemSize) {
    CircularBuffer_t * buffer = memMang_malloc(sizeof(CircularBuffer_t));
    buffer->items = memMang_malloc(maxItemCount * itemSize);
    buffer->firstItemIndex = 0;
    buffer->firstFreeIndex = 0;
    buffer->currentItemCount = 0;
    buffer->maxItemCount = maxItemCount;
    buffer->itemSize = itemSize;
    return buffer;
}

bool cbuf_add(CircularBuffer_t * buffer, void * item) {
    if (cbuf_isFull(buffer)) {
        return false;
    }
    uint8_t bytesToCopy = buffer->itemSize;
    uint8_t * dataToCopy = (uint8_t *)&item;
    uint8_t * bufferBytePtr = &buffer->items[buffer->firstFreeIndex * buffer->itemSize];
    while (bytesToCopy--) {
        (*bufferBytePtr++) = *dataToCopy++;
    }
    buffer->firstFreeIndex = (buffer->firstFreeIndex + 1) % buffer->maxItemCount;
    buffer->currentItemCount++;
    return true;
}

bool cbuf_get(CircularBuffer_t * buffer, void * returnBuffer) {
    if (cbuf_isEmpty(buffer)) {
        return false;
    }
    uint8_t bytesToCopy = buffer->itemSize;
    uint8_t * returnBufferBytePtr = returnBuffer;
    uint8_t * dataToCopy = (uint8_t *)&buffer->items[buffer->firstItemIndex * buffer->itemSize];
    while (bytesToCopy--) {
        (*returnBufferBytePtr++) = *dataToCopy++;
    }
    buffer->currentItemCount--;
    buffer->firstItemIndex = (buffer->firstItemIndex + 1) % buffer->maxItemCount;
    return true;
}

bool cbuf_isFull(CircularBuffer_t * buffer) {
    return buffer->currentItemCount && buffer->firstItemIndex == buffer->firstFreeIndex;
}

bool cbuf_isEmpty(CircularBuffer_t * buffer) {
    return !buffer->currentItemCount && buffer->firstItemIndex == buffer->firstFreeIndex;
}
