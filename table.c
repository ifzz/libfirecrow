#include "table.h"

/* todo: add level argumnet to this */
int hash_key(struct table *tbl, char *key){
	int pre_key = 0;	
	int hash_num = START_LEVEL_SIZE;
	int start = 1;
	char *k = key;
	while(*k != '\0'){
		pre_key += *k;
		k++;
	}
	while(start++ < tbl->level){
		hash_num += START_LEVEL_SIZE;
	}
	/*
	printf("%d %d\n",pre_key, hash_num);
	*/
	return pre_key % hash_num;
}

struct table *table_alloc(){
	struct table *tbl;
	tbl = (struct table *) malloc(sizeof(struct table));
	tbl->slots = (struct table_item*) malloc(sizeof(struct table_item *)* START_LEVEL_SIZE);
	tbl->size = 0;
	tbl->level = 1;
}

void table_free(struct table *tbl){
	free(tbl->slots);
	free(tbl);
}

void table_add(struct table *tbl, char *key, void *item){
	struct table_item *new_item = (struct table_item *) malloc(sizeof(struct table_item));
	new_item->key_val = key;
	new_item->bucket_key = hash_key(tbl, key);
	new_item->content = item;

	struct table_item *start = (tbl->slots+new_item->bucket_key);
	if(start == NULL){
		start += new_item->bucket_key;
		start = new_item;
		tbl->size++;
	}else{
		while(start->next != NULL){
			start = start->next;
		}
		start->next = new_item;
		tbl->size++;
	}
}

#ifdef DEBUG 
void table_print_debug(struct table *tbl, FILE *stream){
	fprintf(stream, "<table p:%p size:%lu level:%d >\n", tbl, tbl->size, tbl->level);
	/* todo: add slots taken/available and total slot size */

	/* table data */
		/* climb slots */
		/* climb to the end of each slot */
		/* present data about how many queries it takes to get to each item */

}
#endif
/*
void *table_get(struct table *tbl, void *key);
void *table_remove(struct table *tbl, void *key);
*/
