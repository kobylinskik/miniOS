#ifndef __LIST__
#define __LIST__

#include "memory.h"
#include <stdint.h>

typedef struct listNode {
    uint64_t * value;
    struct listNode * next;
} listNode_t;

listNode_t * createList();
void * get(listNode_t * head, uint8_t nodeIndex);
void add(listNode_t * head, void * value);

#endif