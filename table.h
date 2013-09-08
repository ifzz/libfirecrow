#include <stdio.h>
#include <stdlib.h>
#define START_LEVEL_SIZE 7

struct table {
	int *slots;
	size_t size;
	int level;
};

struct table_item {
	void *content;
	struct table_item *next;
};

struct table *table_alloc();
void table_free(struct table *tbl);

void table_add(struct table *tbl, char *key, void *item);
void *table_get(struct table *tbl, char *key);
void *table_remove(struct table *tbl, void *key);
int hash_key(struct table *tbl, char *key);

