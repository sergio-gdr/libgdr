#include <assert.h>
#include <stdio.h>
#include "list.h"

static inline void test_list_insert() {
	List(int, list);
	list_init(list);
	list_insert(list, 1);
	list_insert(list, 2);
	list_insert(list, 3);

	int val;
	int iter = 1;
	LIST_FOR_EACH(val, list) {
		assert(val == iter);
		iter++;
	}
	printf("test_list_insert passed\n");
}

int main() {
	test_list_insert();
}
