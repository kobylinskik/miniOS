#ifndef __MUTEX__
#define __MUTEX__

#include "memory.h"
#include <stdbool.h>

typedef bool mutex_t;

mutex_t * mtx_createMutex(void);

// Returns true if mutex acquisition is successful, false otherwise
bool mtx_take(mutex_t * mutex);

// Returns true if mutex release is successful, false otherwise
bool mtx_give(mutex_t * mutex);

#endif