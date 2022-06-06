#ifndef __THREAD__
#define __THREAD__

#include "memory.h"
#include "osConfig.h"
#include "stm32f10x.h"
#include <stdint.h>

typedef struct thread {
    void (*task)(void);
    uint32_t * stackPtr;
    uint32_t stack[THREAD_STACK_SIZE];
    uint32_t delayTicks;
} Thread_t;

Thread_t * thd_createThread(void (*task)());
void thd_delay(Thread_t * thread, uint32_t ticks);

#endif