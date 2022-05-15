#include "threadManager.h"

threadManager_t * createThreadManager(void) {
    threadManager_t * manager = allocateMemory(sizeof(threadManager_t));
    manager->threadList = createThreadList();
    return manager;
};

void addThread(threadManager_t * threadManager, void (*task)(void)) {
    tl_addThread(threadManager->threadList, task);
}

void switchThread(threadManager_t * threadManager) {
    threadManager->threadList = threadManager->threadList->next;
    threadManager->currentThread = threadManager->threadList->thread;
};