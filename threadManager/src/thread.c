#include "thread.h"

void setThreadStack(thread_t * thread) {
    *thread->stackPtr-- = 0x01000000;
    *thread->stackPtr-- = (uint32_t)thread->task;
    *thread->stackPtr-- = (uint32_t)thread->task;

    for (uint8_t i = 0; i < 5; i++) {
        *thread->stackPtr-- = 0;
    }
    *thread->stackPtr-- = 0xFFFFFFF9;
    for (uint8_t i = 0; i < 8; i++) {
        *thread->stackPtr-- = 0;
    }
}

thread_t * createThread(void (*task)()) {
    thread_t * thread = allocateMemory(sizeof(thread_t));
    thread->task = task;
    thread->stackPtr = thread->stack + THREAD_STACK_SIZE - 1;
    setThreadStack(thread);
    return thread;
};
