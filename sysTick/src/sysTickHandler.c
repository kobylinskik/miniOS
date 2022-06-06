#include "sysTickHandler.h"

#define PUSH_THREAD_REGISTERS                                                                                                                                                                          \
    __asm__("PUSH {r11,r10,r9,r8,r7,r6,r5,r4}\n\t"                                                                                                                                                     \
            "STR sp,%0\n\t"                                                                                                                                                                            \
            : "=m"(threadManager->currentThread->stackPtr))

#define POP_THREAD_REGISTERS                                                                                                                                                                           \
    __asm__("LDR sp,%0\n\t"                                                                                                                                                                            \
            "POP {r4-r11}\n\t"                                                                                                                                                                         \
            : "=m"(threadManager->currentThread->stackPtr))

void SysTick_Handler(void) {
    PUSH_THREAD_REGISTERS;

    thdMang_countDownDelays(threadManager);
    thdMang_switchThread(threadManager);

    POP_THREAD_REGISTERS;
}