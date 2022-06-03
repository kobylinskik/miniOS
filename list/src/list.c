#include "list.h"

listNode_t * createList() {
    listNode_t * head = memMang_malloc(sizeof(listNode_t));
    head->value = 0;
    head->next = 0;
    return head;
}

void * get(listNode_t * head, uint8_t nodeIndex) {
    while (nodeIndex--) {
        head = head->next;
    }
    return (void *)head->value;
}

void add(listNode_t * head, void * value) {
    while (head->value != 0 && head->next != 0) {
        head = head->next;
    }
    if (head->value != 0) {
        head->next = memMang_malloc(sizeof(listNode_t));
        head = head->next;
    }
    head->value = (uint64_t *)value;
    head->next = 0;
}