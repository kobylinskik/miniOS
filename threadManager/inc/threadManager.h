#ifndef __THREAD_MANAGER__
#define __THREAD_MANAGER__

#include "thread.h"
#include "threadList.h"

typedef struct {
    Thread_t * idleThread;
    Thread_t * currentThread;
    ThreadListNode_t * threadList;
} ThreadManager_t;

ThreadManager_t * thdMang_createThreadManager(void (*idleTask)(void));
void thdMang_addThread(ThreadManager_t * threadManager, void (*task)(void));
void thdMang_switchThread(ThreadManager_t * threadManager);
void thdMang_countDownDelays(ThreadManager_t * threadManager);
void thdMang_start(ThreadManager_t * threadManager);

#endif