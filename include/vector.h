#ifndef LIBC_VEC_H
#define LIBC_VEC_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define VEC_INIT_CAP 200

#define Vec(type, ...) \
	struct vec##type { \
		size_t size; \
		size_t capacity; \
		type *arr; \
	} __VA_OPT__(__VA_ARGS__)

#define vec_init(vec) \
	do { \
		(vec).size = 0; \
		(vec).capacity = VEC_INIT_CAP; \
		(vec).arr = calloc(1, sizeof(*((vec).arr)) * VEC_INIT_CAP); \
	} while (0);

#define vec_put(vec, value) \
	do { \
		if ((vec).size == (vec).capacity-1) { \
			/* TODO: check overflow */ \
			typeof(*(vec).arr) *array_re = realloc((vec).arr, (vec).capacity*2*sizeof(*(vec).arr)); \
			if (!array_re) { \
				perror("realloc():"); \
				exit(-1); \
			} \
			(vec).arr = array_re; \
			(vec).capacity *= 2; \
		} \
		(vec).arr[(vec).size++] = value; \
	} while (0);

#define vec_erase(vec, idx) \
	(vec).size--; \
	memmove((vec).arr+idx, (vec).arr+idx+1, (vec).size);

#define vec_get(vec, idx) \
	(vec).arr[idx]

#define vec_get_cap(vec) \
	(vec).capacity;

#endif
