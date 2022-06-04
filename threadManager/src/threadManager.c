#include "threadManager.h"

ThreadManager_t * thdMang_createThreadManager(void (*idleTask)(void)) {
    ThreadManager_t * manager = memMang_malloc(sizeof(ThreadManager_t));
    manager->threadList = tl_createThreadList();
    manager->idleThread = thd_createThread(idleTask);
    manager->currentThread = manager->idleThread;
    return manager;
}

void thdMang_addThread(ThreadManager_t * threadManager, void (*task)(void)) {
    tl_addThread(threadManager->threadList, task);
}

void thdMang_switchThread(ThreadManager_t * threadManager) {
    ThreadListNode_t * firstThreadListNode = threadManager->threadList;
    do {
        threadManager->threadList = threadManager->threadList->next;
    } while (threadManager->threadList->thread->delayTicks && threadManager->threadList != firstThreadListNode);

    threadManager->currentThread = threadManager->threadList->thread;

    if (threadManager->currentThread->delayTicks) {
        threadManager->currentThread = threadManager->idleThread;
    }
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

void thdMang_start(ThreadManager_t * threadManager) {
    threadManager->idleThread->task();
}