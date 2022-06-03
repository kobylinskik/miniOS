#ifndef __THREAD_MANAGER__
#define __THREAD_MANAGER__

#include "thread.h"
#include "threadList.h"

typedef struct {
    thread_t * currentThread;
    threadListNode_t * threadList;
} threadManager_t;

threadManager_t * thdMang_createThreadManager(void);
void thdMang_addThread(threadManager_t * threadManager, void (*task)(void));
void thdMang_switchThread(threadManager_t * threadManager);

#endif