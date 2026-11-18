#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "pool.h"

struct pool {
	size_t cap;
	size_t size;
	size_t size_elem;
	size_t align;
	size_t num_chunks;
	uint8_t **chunks;
	__attribute__((__aligned__(alignof(max_align_t)))) uint8_t mem[];
};

pool_t *_pool_create(size_t size_elem, size_t align) {
	pool_t *pool = calloc(1, size_elem*INIT_POOL_SIZE + sizeof(*pool));
	pool->cap = INIT_POOL_SIZE;
	pool->size = 0;
	pool->size_elem = size_elem;
	pool->align = align;
	pool->chunks = calloc(1, sizeof(*pool->chunks));
	pool->chunks[0] = pool->mem;
	pool->num_chunks = 1;

	return pool;
}

void *pool_allocate(pool_t *pool, size_t size) {
	if (pool->size+size > pool->cap) {
		void *tmp = realloc(pool->chunks, sizeof(*pool->chunks) * (pool->num_chunks + 1));
		if (!tmp) {
			perror("realloc():");
			return NULL;
		}
		pool->chunks[pool->num_chunks] = aligned_alloc(pool->align, (pool->size_elem*INIT_POOL_SIZE));
		pool->num_chunks++;
		if (pool->size < pool->cap) {
			pool->size = pool->cap;
		}
		pool->cap *= 2;
	}
	size_t chunk_idx = pool->size/INIT_POOL_SIZE;
	size_t mem_idx = (pool->size*pool->size_elem)%INIT_POOL_SIZE;
	void *ret = &pool->chunks[chunk_idx][mem_idx];
	pool->size += size;

	return ret;
}

void pool_destroy(pool_t *pool) {
	for (int i = 1; i < pool->num_chunks; i++) {
		free(pool->chunks[i]);
	}
	free(pool->chunks);
	free(pool);
}
