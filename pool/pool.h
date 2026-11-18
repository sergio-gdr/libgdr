#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>

typedef struct pool pool_t;

#define INIT_POOL_SIZE 256

pool_t *pool_create(size_t size_elem, size_t align);
void pool_destroy(pool_t *pool);

void *pool_allocate(pool_t *pool, size_t size);
