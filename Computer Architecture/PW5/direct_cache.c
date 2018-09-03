#include "direct_cache.h"
#include "bits.h"
#include "math.h"

struct direct_cache *direct_cache_create(int nb_blocks) {
	struct direct_cache *dirCache;
	dirCache = (struct direct_cache*) calloc(1, sizeof(struct direct_cache));
	dirCache->nb_blocks = nb_blocks;
	dirCache->table = (struct block*) calloc(nb_blocks * nb_blocks, sizeof(struct block));
	printf("Cache of size %d was created\n", dirCache->nb_blocks);
	return dirCache;
}

void direct_cache_delete(struct direct_cache *c) {
	if (!c) {
		fprintf(stderr, "Error in direct_cache_delete function. Cache was not crerated!\n");
	}
	else {
		free(c->table);
		free(c);
		printf("Cache was deleted\n");
	}
}

void direct_cache_print(struct direct_cache *c) {
	if (c == NULL) {
		printf("Non-initialized direct cache: %p\n", c);
		return;
	}
	printf("Number of blocks: %d\n", (c->nb_blocks == 0 ? 0 : (0x1 << c->nb_blocks)));
	if (c->table == NULL) {
		printf("Nn-initialized table: %p\n", c->table);
		return;
	}
	int T = (c->nb_blocks == 0 ? 0 : (0x1 << c->nb_blocks));
	printf("--------------------------------Table:------------------------------------\n");
	for (int i = 0; i < T; i++) {
		printf("Tag: %10d | Valid: %1d | Word:", c->table[i].tag, c->table[i].valid);
		print_bits(c->table[i].word);
	}
	printf("--------------------------------------------------------------------------\n");
	return;
}

int get_offset(int address, struct direct_cache *c) {
	if (!c) {
		fprintf(stderr, "Error in get_offset function. Direct cache is not defined!\n");
		return -1;
	}

	return SWORD(address, 0, (int) log2(c->nb_blocks));
}

int get_index(int address, struct direct_cache *c) {
	if (!c) {
		fprintf(stderr, "Error in get_index function. Direct cache is not defined!\n");
		return -1;
	}
	
	return SWORD(address, (int) log2(c->nb_blocks), (int) log2(c->nb_blocks));
}

int get_tag(int address, struct direct_cache *c) {
	if (!c) {
		fprintf(stderr, "Error in get_tag function. Direct cache is not defined!\n");
		return -1;
	}

	return SWORD(address, 2 * (int) log2(c->nb_blocks), 32 - 2 * (int) log2(c->nb_blocks));
}

int set_direct_cache(int address, int word, struct direct_cache *c) {
	int tag = get_tag(address, c);
	int index = get_index(address, c);
	int offset = get_offset(address, c);

	c->table[index].tag = tag;
	c->table[index].valid = 1;
	c->table[index].word = word;

	return 0;
}

int lw_direct_cache(int *reg, int address, struct direct_cache *c) {
	int tag = get_tag(address, c);
	int index = get_index(address, c);
	int offset = get_offset(address, c);

	if (c->table[index].valid == 1 && c->table[index].tag == tag) {
		*reg = c->table[index].word;
		return 0;
	}
	*reg = -1;

	return 1;
}
