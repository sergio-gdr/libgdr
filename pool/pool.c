#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "pool.h"

struct pool {
	size_t cap;
	size_t size;
	size_t align_offset;
	uint8_t mem[];
};

pool_t *_pool_create(size_t size_elem, size_t align) {
	size_t align_offset = align - ((offsetof(struct pool, mem)%align));
	pool_t *pool = aligned_alloc(align, (size_elem*INIT_POOL_SIZE + sizeof(*pool)) + align_offset);
	pool->cap = INIT_POOL_SIZE;
	pool->size = 0;
	pool->align_offset = align_offset;

	return pool;
}

void *pool_allocate(pool_t *pool, size_t size) {
	void *ret = &pool->mem[pool->size] + pool->align_offset;
	pool->size += size;
	return ret;
}

