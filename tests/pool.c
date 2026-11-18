#include <assert.h>
#include <stdio.h>

#include "pool/pool.h"

#define is_aligned(addr, align) \
	(uintptr_t)addr % align == 0

#define print_alignment(address, alignment) \
	printf("address %p, alignment %lu\n", address, alignment);

static inline void test_pool_alignment_basic_types() {
	// test alignof(char)
	char *ch;
	pool_t *ch_pool = pool_create(typeof(*ch));
	ch = pool_allocate(ch_pool, 1);

	print_alignment(ch, alignof(typeof(*ch)));
	assert(is_aligned(ch, alignof(typeof(*ch))));
	free(ch_pool);

	// test alignof(short)
	short *sh;
	pool_t *sh_pool = pool_create(typeof(*sh));
	sh = pool_allocate(sh_pool, 1);

	print_alignment(sh, alignof(typeof(*sh)));
	assert(is_aligned(sh, alignof(typeof(*sh))));
	free(sh_pool);

	printf("test_pool_alignment_basic_types passed\n");
}

static inline void test_pool_create() {
	pool_t *pool = pool_create(int);
	assert(pool);
	free(pool);

	printf("test_pool_create passed\n");
}

int main() {
	test_pool_create();
	test_pool_alignment_basic_types();
}
