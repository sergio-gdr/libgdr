#include <assert.h>
#include <stdio.h>
#include "list.h"

static inline void test_list_insert() {
	List(int, list);
	list_init(list);
	node_t *n1 = list_insert_new(list, 1);
	node_t *n2 = list_insert_new(list, 2);
	node_t *n3 = list_insert_new(list, 3);

	int val;
	int iter = 1;
	LIST_FOR_EACH(val, list) {
		assert(val == iter);
		iter++;
	}
	list_remove_node_free(list, n1);
	list_remove_node_free(list, n2);
	list_remove_node_free(list, n3);

	printf("test_list_insert passed\n");
}

int main() {
	test_list_insert();
}
