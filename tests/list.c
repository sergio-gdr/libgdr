#include <assert.h>
#include <stdio.h>
#include "list.h"

static inline void test_list_insert() {
	List(int, list);
	node_t *node1 = list_insert_new(list, 1);
	node_t *node2 = list_insert_new(list, 2);
	node_t *node3 = list_insert_new(list, 3);
	node_t *node4 = list_insert_new(list, 4);
	node_t *node5 = list_insert_new(list, 5);
	int iter = 1;
	int *val;
	LIST_FOR_EACH(val, list) {
		assert(*val == iter);
		iter++;
	}
	free(node1);
	free(node2);
	free(node3);
	free(node4);
	free(node5);

	printf("test_list_insert passed\n");
}

int main() {
	test_list_insert();
}
