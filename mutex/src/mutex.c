#include "mutex.h"

mutex_t * mtx_createMutex(void) {
    mutex_t * mutex = memMang_malloc(sizeof(mutex_t));
    *mutex = false;
    return mutex;
}

bool mtx_take(mutex_t * mutex) {
    if (*mutex) {
        return false;
    }
    *mutex = true;
    return true;
}

bool mtx_give(mutex_t * mutex) {
    if (*mutex) {
        *mutex = false;
        return true;
    }
    return false;
}