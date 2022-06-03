#include "threadList.h"

threadListNode_t * tl_createThreadList(void) {
    threadListNode_t * head = memMang_malloc(sizeof(threadListNode_t));
    head->thread = 0;
    head->next = 0;
    return head;
}

void tl_addThread(threadListNode_t * head, void (*task)(void)) {
    threadListNode_t * currentNode = head;
    if (head->thread != 0) {
        while (currentNode->next != head) {
            currentNode = currentNode->next;
        }
        currentNode->next = memMang_malloc(sizeof(threadListNode_t));
        currentNode = currentNode->next;
    }
    currentNode->thread = thd_createThread(task);
    currentNode->next = head;
}