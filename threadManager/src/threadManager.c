#include "threadManager.h"

threadManager_t * thdMang_createThreadManager(void) {
    threadManager_t * manager = memMang_malloc(sizeof(threadManager_t));
    manager->threadList = tl_createThreadList();
    return manager;
};

void thdMang_addThread(threadManager_t * threadManager, void (*task)(void)) {
    tl_addThread(threadManager->threadList, task);
}

void thdMang_switchThread(threadManager_t * threadManager) {
    threadManager->threadList = threadManager->threadList->next;
    threadManager->currentThread = threadManager->threadList->thread;
};