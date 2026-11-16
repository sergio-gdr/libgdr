#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>

typedef struct pool pool_t;

void *pool_allocate(pool_t *pool, size_t num);

#define INIT_POOL_SIZE 256

#define pool_create(type) \
({ \
	struct pool { \
		size_t size; \
		size_t align; \
		__attribute__((aligned(alignof(type)))) uint8_t mem[]; \
	}; \
	calloc(1, sizeof(struct pool) + sizeof(type)*INIT_POOL_SIZE); \
})
