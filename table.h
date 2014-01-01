#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define START_LEVEL_SIZE 7
#define MAX_RATIO 0.5 

struct table {
	struct table_item **slots;
	size_t size;/* items in hashtable */
	int level;
	int depth;
};

struct table_item {
	char *content;/* can be anything */
	char *key_val;/* must be null terminated C string */
	size_t bucket_key;
	struct table_item *next;
};

struct table *table_alloc();
void table_free(struct table *tbl);

void table_add(struct table *tbl, char *key, char *item);
void table_add_item(struct table *tbl, struct table_item *item);
void *table_get(struct table *tbl, char *key);
void *table_remove(struct table *tbl, void *key);
int hash_key(struct table *tbl, char *key);
void table_increase_size(struct table *tbl);
int size_by_level(int level);

#ifdef DEBUG
void *print_table_debug(struct table *tbl, FILE *stream);
#endif
