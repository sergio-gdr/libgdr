#include "pool/pool.h"

int main() {
	typedef struct pool_elem {
		int a;
		float b;
		char c;
		struct pool_elem *elem;
	} pool_elem_t;

	pool_t *pool = pool_create(pool_elem_t);
}
