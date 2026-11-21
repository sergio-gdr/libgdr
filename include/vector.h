#ifndef LIBC_VEC_H
#define LIBC_VEC_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define VEC_INIT_CAP 200

typedef struct vector {
	size_t size;
	size_t capacity;
	void **ptr_arr;
} vec_t;

static void _cleanup_vec(void *l) {
	vec_t *vec = l;
	printf("cleanup vec %p\n", *vec->ptr_arr);
	free(*vec->ptr_arr);
}
#define Vec(type, ...) \
	struct vec##type { \
		vec_t inner; \
		type *arr; \
	} __VA_OPT__(;) \
	__VA_OPT__(__attribute__((cleanup(_cleanup_vec))) struct vec##type __VA_ARGS__ = { .inner.size = 0, .inner.capacity = VEC_INIT_CAP, .arr = calloc(1, sizeof(*((__VA_ARGS__).arr)) * VEC_INIT_CAP), .inner.ptr_arr = (void**)&__VA_ARGS__.arr }) \

#define vec_put(vec, value) \
	do { \
		if ((vec).inner.size == (vec).inner.capacity-1) { \
			/* TODO: check overflow */ \
			typeof(*(vec).arr) *array_re = realloc((vec).arr, (vec).inner.capacity*2*sizeof(*(vec).arr)); \
			if (!array_re) { \
				perror("realloc():"); \
				exit(-1); \
			} \
			(vec).arr = array_re; \
			(vec).inner.capacity *= 2; \
		} \
		(vec).arr[(vec).inner.size++] = value; \
	} while (0);

#define vec_erase(vec, idx) \
	(vec).inner.size--; \
	memmove((vec).arr+idx, (vec).arr+idx+1, (vec).inner.size);

#define vec_get(vec, idx) \
	(vec).arr[idx]

#define vec_get_cap(vec) \
	(vec).inner.capacity;

#endif
