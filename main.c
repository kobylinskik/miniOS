#include "memory.h"
#include <stdint.h>

int main() {
    initHeap();
    int * t1 = allocateMemory(8);
    int * t2 = allocateMemory(5);
    int * t3 = allocateMemory(13);
    int * t4 = allocateMemory(30);
    freeMemory(t1);
    int * t5 = allocateMemory(2);
    while (1) {
    }
}