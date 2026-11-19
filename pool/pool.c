#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "pool.h"

void *pool_allocate(pool_t *pool, size_t size) {
	if (pool->size+size > pool->cap) {
		void *new_mem;
		new_mem = realloc(pool->num_chunks_lists > 1 ? pool->chunks_lists : NULL, sizeof(*pool->chunks_lists) * (pool->num_chunks_lists + 1));
		if (!new_mem) {
			perror("realloc():");
			return NULL;
		}
		if (pool->num_chunks_lists == 1) {
			void *tmp = pool->chunks_lists;
			pool->chunks_lists = new_mem;
			pool->chunks_lists[0] = tmp;
		}
		pool->chunks_lists = new_mem;
		pool->chunks_lists[pool->num_chunks_lists] = aligned_alloc(pool->align, pool->align*pool->chunk_cap);
		pool->num_chunks_lists++;
		if (pool->size < pool->cap) {
			pool->size = pool->cap;
		}
		pool->cap *= 2;
	}
	size_t mem_idx = (pool->size)%pool->chunk_cap;
	size_t chunk_idx = pool->size/pool->chunk_cap;
	pool->size += size;
	if (pool->num_chunks_lists > 1) {
		return &pool->chunks_lists[chunk_idx][mem_idx];
	}
	uint8_t *mem = (uint8_t*)pool->chunks_lists;
	return &mem[mem_idx*pool->align];
}

void pool_destroy(pool_t *pool) {
	for (int i = 1; i < pool->num_chunks_lists; i++) {
		free(pool->chunks_lists[i]);
	}
	if (pool->num_chunks_lists > 1)
		free(pool->chunks_lists);
	free(pool);
}
