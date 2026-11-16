#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "pool.h"

#define INIT_POOL_SIZE 256

void *pool_allocate(pool_t *pool, size_t num);
