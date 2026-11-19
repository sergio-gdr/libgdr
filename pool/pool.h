#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>

typedef struct pool pool_t;
struct pool {
	size_t cap;
	size_t size;
	size_t align;
	size_t chunk_size;
	size_t chunk_cap;
	size_t num_chunks_lists;
	uint8_t **chunks_lists;
};

#define pool_create(__pool_size, __chunk_size, ...) \
({ \
	size_t align = __chunk_size; \
	__VA_OPT__(align = __VA_ARGS__;) \
	pool_t *ret = NULL; \
	struct { \
		pool_t container; \
		__attribute__((__aligned__(__VA_ARGS__))) uint8_t mem[]; \
	} *pool = calloc(1, align*__pool_size + sizeof(*pool)); \
	if (__chunk_size > align) { \
		printf("error: alignment %lu must be multiple of the element size %lu\n", align, __chunk_size); \
	} \
	else { \
		pool->container.cap = __pool_size; \
		pool->container.chunk_cap = __pool_size; \
		pool->container.size = 0; \
		pool->container.chunk_size = __chunk_size; \
		pool->container.align = align; \
		pool->container.chunks_lists = (uint8_t**)&pool->mem; \
		pool->container.num_chunks_lists = 1; \
		ret = &pool->container; \
	} \
	ret; \
})

void pool_destroy(pool_t *pool);

void *pool_allocate(pool_t *pool, size_t size);
