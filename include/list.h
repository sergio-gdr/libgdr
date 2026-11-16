#ifndef LIBGDR_LIST_H
#define LIBGDR_LIST_H

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
	struct node *next;
	uint8_t elem[];
} node_t;

#define List(type, ...) \
	struct list##type { \
		struct node *head; \
		struct node *tail; \
		size_t size; \
		type elem_type; \
	} __VA_OPT__(__VA_ARGS__)

#define list_init(list) \
	do { \
		(list).head = NULL; \
		(list).tail = NULL; \
		(list).size = 0; \
	} while (0);

#define list_insert(list, value) \
	do { \
		typeof((list).elem_type) elem = value; \
		node_t *node = calloc(1, sizeof(*node)+sizeof(elem)); \
		memcpy(node->elem, &elem, sizeof(elem)); \
		(list).tail = node; \
		(list).tail->next = node; \
	} while (0);

#define list_remove(vec, node) \

#define LIST_FOR_EACH(hold, list) \
		node_t *head = (list).head; \
		while (head && head->next && (hold = (typeof((list).elem_type))head->elem))

#endif
