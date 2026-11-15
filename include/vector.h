#ifndef LIBC_VEC_H
#define LIBC_VEC_H

#include <stddef.h>
#include <stdlib.h>

#define Vec(type, ...) \
	struct vec##type { \
		size_t size; \
		size_t capacity; \
		type *array; \
	} __VA_OPT__(__VA_ARGS__)

#define vec_init(vec) \
	do { \
		(vec).array = calloc(1, sizeof(*((vec).array)) * 200); \
	} while (0);

#define vec_emplace(vec, value) \
	(vec).array[0] = value;

#endif
