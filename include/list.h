#ifndef LIBGDR_LIST_H
#define LIBGDR_LIST_H

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
	struct node *next;
	struct node *prev;
	uint8_t elem[];
} node_t;

#define List(type, ...) \
	struct list##type { \
		struct node *head; \
		struct node *tail; \
		size_t size; \
		type elem_type; \
	} __VA_OPT__(__VA_ARGS__ = { .head = NULL, .tail = NULL, .size = 0 })

#define list_insert_new(list, element) \
	({ \
	 typeof(element) value = element; \
	 node_t *node = calloc(1, sizeof(*node)+sizeof(value)); \
	 memcpy(node->elem, &value, sizeof(value)); \
	 if (!(list).head) { \
		(list).head = (list).tail = node; \
	 } \
	 else { \
		node->prev = (list).tail; \
		node->prev->next = node; \
		(list).tail = node; \
	 } \
	 (list).size++; \
	 node; \
	})

#define list_remove_node_free(list, node) \
	if ((list).head == node) { \
		(list).head = (list).head->next; \
	} \
	else if ((list).tail == node) { \
		(list).tail = (list).tail->prev; \
	} \
	else { \
		node->prev->next = node->next; \
		node->next->prev = node->prev; \
	} \
	free(node);


static inline void list_tmp(void *list) {
	;
}
#define LIST_FOR_EACH(hold, list) \
		node_t *_iter = (list).head; \
		list_tmp(1 ? (hold) : &(list).elem_type); \
		while (_iter && _iter->next && (hold = (typeof(hold))_iter->elem) && (_iter = _iter->next))

#endif
