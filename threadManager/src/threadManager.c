#include "threadManager.h"

ThreadManager_t * thdMang_createThreadManager(void) {
    ThreadManager_t * manager = memMang_malloc(sizeof(ThreadManager_t));
    manager->threadList = tl_createThreadList();
    return manager;
}

void thdMang_addThread(ThreadManager_t * threadManager, void (*task)(void)) {
    tl_addThread(threadManager->threadList, task);
}

void thdMang_switchThread(ThreadManager_t * threadManager) {
    do {
        threadManager->threadList = threadManager->threadList->next;
    } while (threadManager->threadList->thread->delayTicks);

    threadManager->currentThread = threadManager->threadList->thread;
}

void thdMang_countDownDelays(ThreadManager_t * threadManager) {
    ThreadListNode_t * threadListNode = threadManager->threadList;
    do {
        if (threadListNode->thread->delayTicks) {
            threadListNode->thread->delayTicks--;
        }
        threadListNode = threadListNode->next;
    } while (threadListNode != threadManager->threadList);
}