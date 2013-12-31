#include "table.h"

int size_by_level(int level){
	int start = 1;
	int hash_num = START_LEVEL_SIZE;
	while(start++ < level){
		hash_num += START_LEVEL_SIZE;
	}
	return hash_num;
}

/* todo: add level argumnet to this */
int hash_key(struct table *tbl, char *key){
	int pre_key = 0;	
	int hash_num = START_LEVEL_SIZE;
	char *k = key;
	while(*k != '\0'){
		pre_key += *k;
		k++;
	}
	hash_num = size_by_level(tbl->level); 
	return pre_key % hash_num;
}

struct table *table_alloc(){
	struct table *tbl;
	tbl = (struct table *) malloc(sizeof(struct table));
	int slots_num;
	slots_num = size_by_level(tbl->level);
	tbl->slots = (struct table_item **) malloc(sizeof(struct table_item *)* slots_num);
	tbl->size = 0;
	tbl->level = 1;

	size_t i;
	struct table_item **slot = malloc(sizeof(struct table_item **));

	puts("start of table alloc");
	struct table_item **slots = malloc(sizeof(struct table_item **));
	for(i=0; i < slots_num; i++){
		slot = tbl->slots+i;
		*slot = NULL;
	}
	/*
	free(slot);
	*/
	puts(" end of table alloc");
	return tbl;
}

void table_free(struct table *tbl){
	free(tbl->slots);
	free(tbl);
}

void table_add(struct table *tbl, char *key, char *item){
	struct table_item *new_item = (struct table_item *) malloc(sizeof(struct table_item));
	new_item->key_val = key;
	new_item->bucket_key = hash_key(tbl, key);
	new_item->content = item;
	new_item->next = NULL;

	printf("--- allocating item into slot %d ---\n", (int)new_item->bucket_key);
	struct table_item **start_dp = tbl->slots+new_item->bucket_key;
	struct table_item *start = *start_dp;
	if(start == NULL){
		puts("start is null");
		printf("--- allocating item into slot %d ---\n", (int)new_item->bucket_key);
		*start_dp = new_item;
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
	int slots_num;
	slots_num = size_by_level(tbl->level);
	fprintf(stream, "slots:%d\n", slots_num);
	int i;
	struct table_item *slot = malloc(sizeof(struct table_item *));
	for(i=0; i < slots_num; i++){
		if(tbl->slots+i == NULL){
			fprintf(stream, "%d:is null\n", i);
		}else{
			fprintf(stream, "%d:items found\n", i);
			slot = tbl->slots[i];
			fprintf(stream, " +");
			while(slot != NULL){
				fprintf(stream, "-- %s->%s ", slot->key_val, slot->content);
				slot = slot->next;
			}
			fprintf(stream, "\n\n");
		}
	}

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
