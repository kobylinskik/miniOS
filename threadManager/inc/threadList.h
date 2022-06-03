#ifndef __THREAD_LIST__
#define __THREAD_LIST__

#include "memory.h"
#include "thread.h"

typedef struct threadListNode {
    thread_t * thread;
    struct threadListNode * next;
} threadListNode_t;

threadListNode_t * tl_createThreadList(void);
void tl_addThread(threadListNode_t * head, void (*task)(void));

#endif