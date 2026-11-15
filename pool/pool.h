#include <stddef.h>

typedef struct pool {
	size_t size;
	size_t align;
	char mem[];
} pool_t;

pool_t *pool_create(size_t size, size_t align);
void *pool_allocate(pool_t *pool, size_t num);
