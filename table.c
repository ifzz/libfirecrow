#include "table.h"

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
	tbl->level = 1;
}

void table_free(struct table *tbl){
	free(tbl->slots);
	free(tbl);
}

void table_add(struct table *tbl, char *key, void *item){
	struct table_item *new_item = (struct table_item *) malloc(sizeof(struct table_item));
	new_item->char_key = key;
	new_item->int_key = hash_key(tbl, key);
	new_item->content = item;

	struct table_item *start = (tbl->slots+new_item->int_key);
	if(start == NULL){
		(tbl->slots+new_item->int_key) = new_item;
	}
	while(start->next != NULL){
		start = start->next;
	}
	start->next = new_item;
}
/*
void *table_get(struct table *tbl, void *key);
void *table_remove(struct table *tbl, void *key);
*/
