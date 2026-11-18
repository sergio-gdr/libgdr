#include <assert.h>
#include <stddef.h>
#include <stdio.h>

#include "pool/pool.h"

#define is_aligned(addr, align) \
	(uintptr_t)addr % align == 0

#define print_alignment(address, alignment) \
	printf("address %p, alignment %lu\n", address, alignment);

static inline void test_pool_alignment_max_align_t() {
	// test max_align_t
	max_align_t *max;
	pool_t *max_pool = pool_create(typeof(*max));
	max = pool_allocate(max_pool, 1);

	print_alignment(max, alignof(typeof(*max)));
	assert(is_aligned(max, alignof(typeof(*max))));
	pool_destroy(max_pool);

	printf("test_pool_alignment_max_align_t passed\n");
}

static inline void test_pool_alignment_basic_types() {
	// test alignof(char)
	char *ch;
	pool_t *ch_pool = pool_create(typeof(*ch));
	ch = pool_allocate(ch_pool, 1);

	print_alignment(ch, alignof(typeof(*ch)));
	assert(is_aligned(ch, alignof(typeof(*ch))));
	pool_destroy(ch_pool);

	// test alignof(short)
	short *sh;
	pool_t *sh_pool = pool_create(typeof(*sh));
	sh = pool_allocate(sh_pool, 1);

	print_alignment(sh, alignof(typeof(*sh)));
	assert(is_aligned(sh, alignof(typeof(*sh))));
	pool_destroy(sh_pool);

	// test alignof(int)
	int *in;
	pool_t *in_pool = pool_create(typeof(*in));
	in = pool_allocate(in_pool, 1);

	print_alignment(in, alignof(typeof(*in)));
	assert(is_aligned(in, alignof(typeof(*in))));
	pool_destroy(in_pool);

	// test alignof(long)
	long *lo;
	pool_t *lo_pool = pool_create(typeof(*lo));
	lo = pool_allocate(lo_pool, 1);

	print_alignment(lo, alignof(typeof(*lo)));
	assert(is_aligned(lo, alignof(typeof(*lo))));
	pool_destroy(lo_pool);

	// test alignof(long long)
	long long *lolo;
	pool_t *lolo_pool = pool_create(typeof(*lolo));
	lolo = pool_allocate(lolo_pool, 1);

	print_alignment(lolo, alignof(typeof(*lolo)));
	assert(is_aligned(lolo, alignof(typeof(*lolo))));
	pool_destroy(lolo_pool);

	printf("test_pool_alignment_basic_types passed\n");
}

static inline void test_pool_create() {
	pool_t *pool = pool_create(int);
	assert(pool);
	pool_destroy(pool);

	printf("test_pool_create passed\n");
}

int main() {
	test_pool_create();
	test_pool_alignment_basic_types();
	test_pool_alignment_max_align_t();
}
