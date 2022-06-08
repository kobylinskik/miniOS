#ifndef __THREAD_LIST__
#define __THREAD_LIST__

#include "memory.h"
#include "thread.h"

typedef struct ThreadListNode {
    Thread_t * thread;
    struct ThreadListNode * next;
} ThreadListNode_t;

ThreadListNode_t * tl_createThreadList(void);
void tl_addThread(ThreadListNode_t * head, void (*task)(void));

// Removes a threadListNode and returns the previous node
ThreadListNode_t * tl_deleteThread(ThreadListNode_t * nodeToRemove);

#endif