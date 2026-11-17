#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>

typedef struct pool pool_t;

#define INIT_POOL_SIZE 256

void *pool_allocate(pool_t *pool, size_t size);

pool_t *_pool_create(size_t size_elem, size_t align);
#define pool_create(type, ...) \
	_pool_create(sizeof(type), alignof(type));
