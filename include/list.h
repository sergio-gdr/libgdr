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

typedef struct list {
	struct node *head;
	struct node *tail;
	size_t size;
} list_t;

#define LIST_FOR_EACH_SAFE(__node, __list) \
	node_t *__tmp; \
	for (__node = (__list).head, __tmp = __node->next; __node; __node = __tmp, __tmp = __node ? __node->next : NULL)

#define LIST_FOR_EACH(__node, __list) \
	for (__node = (__list).head; __node->next; __node = __node->next)

#define LIST_CLEANUP(_list) \
	node_t *_curr; \
	if ((_list).head) { \
		LIST_FOR_EACH_SAFE(_curr, _list) \
			free(_curr); \
	}

static inline void __cleanup_list(list_t list) {
	LIST_CLEANUP(list);
}

static void _cleanup_list(void *l) {
	list_t *list = l;
	__cleanup_list(*list);
}
#define List(type, ...) \
	struct list##type { \
		list_t inner; \
		type elem_type; \
	}__VA_OPT__(;) \
	__VA_OPT__(__attribute__((cleanup(_cleanup_list))) struct list##type __VA_ARGS__ = {0})

#define list_insert_new(list, element) \
	({ \
	 typeof((list).elem_type) value = element; \
	 node_t *node = calloc(1, sizeof(*node)+sizeof(value)); \
	 memcpy(node->elem, &value, sizeof(value)); \
	 if (!(list).inner.head) { \
		(list).inner.head = (list).inner.tail = node; \
	 } \
	 else { \
		node->prev = (list).inner.tail; \
		node->prev->next = node; \
		(list).inner.tail = node; \
	 } \
	 (list).inner.size++; \
	 node; \
	})

#define list_remove_node_free(list, node) \
	if ((list).inner.head == node) { \
		(list).inner.head = (list).inner.head->next; \
	} \
	else if ((list).tail == node) { \
		(list).inner.tail = (list).inner.tail->prev; \
	} \
	else { \
		node->prev->next = node->next; \
		node->next->prev = node->prev; \
	} \
	free(node);

#endif
