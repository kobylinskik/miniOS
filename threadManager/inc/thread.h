#ifndef __THREAD__
#define __THREAD__

#include "memory.h"
#include "osConfig.h"
#include <stdint.h>

typedef struct thread {
    void (*task)(void);
    uint32_t * stackPtr;
    uint32_t stack[THREAD_STACK_SIZE];
} thread_t;

thread_t * createThread(void (*task)());

#endif