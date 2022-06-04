#include "list.h"
#include "memory.h"
#include "stm32f10x.h"
#include "thread.h"
#include "threadManager.h"
//#include "thread0.h"
//#include "thread1.h"
#include <stdint.h>

ThreadManager_t * threadManager;
Thread_t * currentThread;
ListNode_t * threadList;

uint32_t a = 0;
uint32_t b = 0;
uint32_t c = 0;

void main0() {
    while (1) {
        a++;
        thd_delay(threadManager->currentThread, 1);
    }
}

void main1() {
    while (1) {
        b++;
        thd_delay(threadManager->currentThread, 1);
    }
}

void main2() {
    while (1) {
        c++;
        thd_delay(threadManager->currentThread, 10);
    }
}

void setupSystick(void) {
    SystemCoreClockUpdate();
    SysTick_Config(SystemCoreClock / 100U);
    __enable_irq();
}

void SysTick_Handler(void) {
    //  Push thread registers to stack
    __asm__("PUSH {r11,r10,r9,r8,r7,r6,r5,r4}\n\t"
            "STR sp,%0\n\t"
            : "=m"(threadManager->currentThread->stackPtr));

    thdMang_countDownDelays(threadManager);
    thdMang_switchThread(threadManager);

    // Pop registers from the thread we are switching to
    __asm__("LDR sp,%0\n\t"
            "POP {r4-r11}\n\t"
            : "=m"(threadManager->currentThread->stackPtr));
}

int main() {
    memMang_initHeap();

    threadList = createList();

    Thread_t initialThread;

    /*Thread_t thread0;
    thread0.task = &main0;
    thread0.stackPtr = &thread0.stack[THREAD_STACK_SIZE - 1];
    setThreadStack(&thread0);


    Thread_t thread1;
    thread1.task = &main1;
    thread1.stackPtr = &thread1.stack[THREAD_STACK_SIZE - 1];
    setThreadStack(&thread1);*/

    threadManager = thdMang_createThreadManager();

    thdMang_addThread(threadManager, &main0);
    thdMang_addThread(threadManager, &main1);
    thdMang_addThread(threadManager, &main2);

    /*
    Thread_t * thread0 = createThread(&main0);
    Thread_t * thread1 = createThread(&main1);
    add(threadList, thread0);
    add(threadList, thread1);
    threadList->next->next = threadList;
*/
    threadManager->currentThread = &initialThread;

    setupSystick();

    int x = 0;
    while (1) {
    }
}