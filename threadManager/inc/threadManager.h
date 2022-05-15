#ifndef __THREAD_MANAGER__
#define __THREAD_MANAGER__

#include "thread.h"
#include "threadList.h"

typedef struct {
    thread_t * currentThread;
    threadListNode_t * threadList;
} threadManager_t;

threadManager_t * createThreadManager(void);
void addThread(threadManager_t * threadManager, void (*task)(void));
void switchThread(threadManager_t * threadManager);

#endif