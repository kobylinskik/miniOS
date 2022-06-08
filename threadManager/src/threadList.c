#include "threadList.h"

ThreadListNode_t * tl_createThreadList(void) {
    ThreadListNode_t * head = memMang_malloc(sizeof(ThreadListNode_t));
    head->thread = 0;
    head->next = 0;
    return head;
}

void tl_addThread(ThreadListNode_t * head, void (*task)(void)) {
    ThreadListNode_t * currentNode = head;
    if (head->thread) {
        while (currentNode->next != head) {
            currentNode = currentNode->next;
        }
        currentNode->next = memMang_malloc(sizeof(ThreadListNode_t));
        currentNode = currentNode->next;
    }
    currentNode->thread = thd_createThread(task);
    currentNode->next = head;
}

ThreadListNode_t * tl_deleteThread(ThreadListNode_t * nodeToRemove) {
    ThreadListNode_t * prevNode = nodeToRemove;
    while (prevNode->next != nodeToRemove) {
        prevNode = prevNode->next;
    }
    prevNode->next = nodeToRemove->next;
    memMang_free(nodeToRemove->thread);
    memMang_free(nodeToRemove);
    return prevNode;
}