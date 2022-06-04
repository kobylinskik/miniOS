#ifndef __LIST__
#define __LIST__

#include "memory.h"
#include <stdint.h>

typedef struct listNode {
    uint64_t * value;
    struct listNode * next;
} ListNode_t;

ListNode_t * createList();
void * get(ListNode_t * head, uint8_t nodeIndex);
void add(ListNode_t * head, void * value);

#endif