#include "list.h"
#include "memory.h"
#include "stm32f10x.h"
#include "thread.h"
//#include "thread0.h"
//#include "thread1.h"
#include <stdint.h>

thread_t * currentThread;
listNode_t * threadList;

uint32_t a = 0;
uint32_t b = 0;

void main0() {
    while (1) {
        a++;
    }
}

void main1() {
    while (1) {
        b++;
    }
}

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

void setupSystick(void) {
    SystemCoreClockUpdate();
    SysTick_Config(SystemCoreClock / 100U);
    __enable_irq();
}

void SysTick_Handler(void) {
    // Push thread registers to stack
    __asm__("PUSH {r11,r10,r9,r8,r7,r6,r5,r4}\n\t"
            "STR sp,%0\n\t"
            : "=m"(currentThread->stackPtr));

    threadList = threadList->next;
    currentThread = get(threadList, 0);

    // Pop registers from the thread we are switching to
    __asm__("LDR sp,%0\n\t"
            "POP {r4-r11}\n\t"
            : "=m"(currentThread->stackPtr));
}

int main() {
    initHeap();

    threadList = createList();

    thread_t initialThread;

    thread_t thread0;
    thread0.task = &main0;
    thread0.stackPtr = &thread0.stack[THREAD_STACK_SIZE - 1];
    setThreadStack(&thread0);

    thread_t thread1;
    thread1.task = &main1;
    thread1.stackPtr = &thread1.stack[THREAD_STACK_SIZE - 1];
    setThreadStack(&thread1);

    add(threadList, &thread0);
    add(threadList, &thread1);
    threadList->next->next = threadList;

    currentThread = &initialThread;

    setupSystick();

    int x = 0;
    while (1) {
    }
}