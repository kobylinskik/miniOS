#include "thread.h"

void thd_setThreadStack(thread_t * thread) {
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

thread_t * thd_createThread(void (*task)()) {
    thread_t * thread = memMang_malloc(sizeof(thread_t));
    thread->task = task;
    thread->stackPtr = thread->stack + THREAD_STACK_SIZE - 1;
    thd_setThreadStack(thread);
    return thread;
};
