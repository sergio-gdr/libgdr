#include <assert.h>
#include <stdio.h>
#include "list.h"

List(int) list_recv_arg_and_ret(List(int) list) {
	return list;
}

static inline void test_list_args_and_return() {
	List(int, list);
	List(int, list2);
	list2 = list_recv_arg_and_ret(list);
}

static inline void test_list_insert() {
	List(int, list);
	node_t *node1 = list_insert_new(list, 1);
	node_t *node2 = list_insert_new(list, 2);

	printf("test_list_insert passed\n");
}

int main() {
	test_list_insert();
	test_list_args_and_return();
}
