#include "vector.h"
#include <assert.h>
#include <string.h>

static inline void vec_test_inside_struct() {
	typedef struct {
		Vec(int, test);
	} inside_t;
	inside_t inside;
	vec_init(inside.test);

	vec_put(inside.test, 1);
	int get = vec_get(inside.test, 0);

	assert(get == 1);

	printf("vec_test_inside_struct passed\n");
}

static inline void vec_test_arbitrary_struct() {
	typedef struct arb {
		int a, b, c;
	} arb_t;
	arb_t arb = { .a = 1, .b = 2, .c = 3 };

	Vec(arb_t, arb_str_vec);
	vec_init(arb_str_vec);
	vec_put(arb_str_vec, arb);
	arb_t get_arb = vec_get(arb_str_vec, 0);

	assert(get_arb.a == arb.a && get_arb.b == arb.b && get_arb.c == arb.c);

	printf("vec_test_arbitrary_struct passed\n");
}

static Vec(int) test_args(Vec(int, arg)) {
	assert(vec_get(arg, 0) ==  1);
	return arg;
}

static inline void vec_test_arguments_and_return() {
	Vec(int, test);
	vec_init(test);
	vec_put(test, 1);
	Vec(int, ret) = test_args(test);
	assert(vec_get(ret, 0) == 1);
	printf("vec_test_arguments_and_return passed\n");
}

static inline void vec_test_simple_put_get() {
	typedef char * charptr;
	Vec(charptr, test);
	vec_init(test);

	vec_put(test, "Hello");
	vec_put(test, ", ");
	vec_put(test, "World");
	vec_put(test, "!");
	char *hello = vec_get(test, 0);
	char *comma = vec_get(test, 1);
	char *world = vec_get(test, 2);
	char *exclamation = vec_get(test, 3);
	char *final_str = calloc(1, strlen(hello)+strlen(comma)+strlen(world)+strlen(exclamation)+1);
	strcat(final_str, hello);
	strcat(final_str, comma);
	strcat(final_str, world);
	strcat(final_str, exclamation);
	assert(!strcmp(final_str, "Hello, World!"));
	printf("vec_test_simple_put_get passed\n");
}

static inline void vec_test_realloc() {
	Vec(int, test);
	vec_init(test);
	size_t cap = vec_get_cap(test);

	for (size_t i = 0; i < cap; i++) {
		vec_put(test, i);
	}
	vec_put(test, cap);
	int test_cap = vec_get(test, cap);
	assert(test_cap == cap);
	int new_cap = vec_get_cap(test);
	assert(new_cap == cap*2);
	printf("vec_test_realloc passed\n");
}

int main() {
	vec_test_simple_put_get();
	vec_test_arguments_and_return(); // test that Vec(type) can be used as function arguments
	vec_test_realloc();
	vec_test_arbitrary_struct();
	vec_test_inside_struct();

	return 0;
}
