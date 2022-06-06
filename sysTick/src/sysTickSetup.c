#include "sysTickSetup.h"

void setupSystick(void) {
    SystemCoreClockUpdate();
    SysTick_Config(SystemCoreClock / 100U);
    __enable_irq();
}