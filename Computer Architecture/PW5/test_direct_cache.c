#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "direct_cache.h"

int main() {
	struct direct_cache *c = NULL;
	c = direct_cache_create(4);

	set_direct_cache(0x00000040, 0xFFFF00FF, c);
	set_direct_cache(0x00000044, 0xFFFFFFFF, c);


	direct_cache_print(c);
	printf("\n");
	int word;
	lw_direct_cache(&word, 0x00000040, c);

	direct_cache_delete(c);
	// printf("\n");

	return 0;
}
