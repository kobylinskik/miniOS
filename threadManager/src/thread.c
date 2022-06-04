#include "thread.h"

void thd_setThreadStack(Thread_t * thread) {
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

Thread_t * thd_createThread(void (*task)()) {
    Thread_t * thread = memMang_malloc(sizeof(Thread_t));
    thread->task = task;
    thread->stackPtr = thread->stack + THREAD_STACK_SIZE - 1;
    thread->delayTicks = 0;
    thd_setThreadStack(thread);
    return thread;
}

void thd_delay(Thread_t * thread, uint32_t ticks) {
    thread->delayTicks = ticks;
    SysTick->VAL = 0;
    SCB->ICSR |= SCB_ICSR_PENDSTSET;
}