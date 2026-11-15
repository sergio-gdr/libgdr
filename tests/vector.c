#include "vector.h"

typedef int * intptr;
typedef struct sample {
	int a;
	float b;
	Vec(int, vec1);
	Vec(intptr, vec2);
} sample_t;

Vec(int) tmp(Vec(int, array)) {
	Vec(int, array2);
	return array2;
}

int main() {
	Vec(int, *array);
	array = calloc(1, sizeof(*array));
	Vec(sample_t, samp);
	vec_init(*array);
	vec_init(samp);
	vec_emplace(samp, 1);
	vec_emplace(*array, 1);
	tmp(*array);
}
