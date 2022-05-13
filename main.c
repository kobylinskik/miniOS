#include "list.h"
#include "memory.h"
#include "stm32f10x.h"
#include "thread.h"
#include "thread0.h"
#include <stdint.h>

thread_t * currentThread;

void setThreadStack(thread_t * thread) {
    *thread->stackPtr-- = 0x41000000;
    *thread->stackPtr-- = (uint32_t)thread->task;
    *thread->stackPtr-- = (uint32_t)thread->task;
    //*thread->stackPtr-- = 0xFFFFFFF9;
    for (uint8_t i = 0; i < 12; i++) {
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

    // Get stack frame size from generated machine code
    // arm-none-eabi-gcc uses R7 as a stack frame pointer
    __asm__("LDR r5,%0\n\t"
            "LDRB r4,[r5]\n\t"
            "MOV r6,#0xF\n\t"
            "AND r4,r4,r6\n\t"
            "MOV r6,#4\n\t"
            "MUL r4,r4,r6\n\t"
            "STRB r4,%1"
            : "=m"(handlerAddr)
            : "m"(frameSize));

    /*__asm__("LDR r0,%0\n\t"
            "LDRB r1,%1\n\t"
            "ADD r2,sp,r1\n\t"
            "STR r2,[r0]"
            : "=m"(stackPtrAddr)
            : "m"(frameSize));*/
    // currentThread = currentThread->next;

    // Push thread registers to its stack

    /* __asm__("PUSH {r4-r11}\n\t"
             "LDRB r0,%1\n\t"
             "SUB r7,sp,r0\n\t"
             "SUB r7,#16"
             : "=m"(currentThread->stackPtr)
             : "m"(frameSize));

     currentThread = currentThread->next;*/

    // Pop registers from the thread we are switching to
    __asm__("LDR sp,%0\n\t"
            "LDRB r0,%1\n\t"
            "POP {r4-r11}\n\t"
            "SUB r7,sp,r0\n\t"
            "SUB r7,r7,#4\n\t"
            : "=m"(currentThread->stackPtr)
            : "m"(frameSize));
}

int main() {
    initHeap();

    thread_t thread0;
    thread0.task = &main0;
    thread0.stackPtr = &thread0.stack[THREAD_STACK_SIZE - 1];
    setThreadStack(&thread0);

    currentThread = &thread0;

    setupSystick();

    int x = 0;
    while (1) {
    }
}