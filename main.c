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
    for (uint8_t i = 0; i < 7; i++) {
        *thread->stackPtr-- = 0;
    }
}

void setupSystick(void) {
    SystemCoreClockUpdate();
    SysTick_Config(SystemCoreClock / 100U);
    __enable_irq();
}

void SysTick_Handler(void) {
    uint32_t handlerAddr = (uint32_t)&SysTick_Handler;
    handlerAddr++;
    uint8_t frameSize = 0;

    threadList = threadList->next;

    // Get stack frame size from generated machine code
    // arm-none-eabi-gcc uses R7 as a stack frame pointer
    __asm__("LDR r1,%0\n\t"
            "LDRB r0,[r1]\n\t"
            "MOV r2,#0xF\n\t"
            "AND r0,r0,r2\n\t"
            "MOV r2,#4\n\t"
            "MUL r0,r0,r2\n\t"
            "STRB r0,%1"
            : "=m"(handlerAddr)
            : "m"(frameSize));

    __asm__( //"SUB sp,%1\n\t"
        "PUSH {r11,r10,r9,r8,r7,r6,r5,r4}\n\t"
        "STR sp,%0\n\t"
        : "=m"(currentThread->stackPtr)
        : "m"(frameSize));

    currentThread = get(threadList, 0);

    // Pop registers from the thread we are switching to
    __asm__("LDRB r0,%1\n\t"
            "LDR sp,%0\n\t"
            "POP {r4-r11}\n\t"
            "PUSH {r7}\n\t"
            "SUB r7,sp,r0\n\t"
            : "=m"(currentThread->stackPtr)
            : "m"(frameSize));
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