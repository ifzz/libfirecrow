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
	tbl->depth = 0;

	size_t i;
	struct table_item **slot;
	for(i=0; i < slots_num; i++){
		slot = tbl->slots+i;
		*slot = NULL;
	}
	return tbl;
}

void table_free(struct table *tbl){
	free(tbl->slots);
	free(tbl);
}

int table_increase_size(struct table *tbl){
	int level = tbl->level+1;
	/*
	allocate new slots
	cpy pointer to old slots
	replay all items into new slots
	*/
	return level;
}

void table_add_item(struct table *tbl, struct table_item *item){
	int depth = 1;
	struct table_item **start_dp = tbl->slots+item->bucket_key;
	struct table_item *start = *start_dp;
	if(start == NULL){
		*start_dp = item;
		tbl->size++;
	}else{
		depth++;
		while(start->next != NULL){
			start = start->next;
			depth++;
		}
		start->next = item;
		tbl->size++;
	}
	if(tbl->depth < depth){
		tbl->depth = depth;
	}
	if(tbl->depth > DEPTH_MARGIN){
		table_increase_size(tbl);
	}
}

void table_add(struct table *tbl, char *key, char *item){
	struct table_item *new_item = (struct table_item *) malloc(sizeof(struct table_item));
	new_item->key_val = key;
	new_item->bucket_key = hash_key(tbl, key);
	new_item->content = item;
	new_item->next = NULL;
	table_add_item(tbl, new_item);
}

void *table_get(struct table *tbl, char *key){
	int bucket_key = hash_key(tbl, key);
	struct table_item *item;
	item = *(tbl->slots+bucket_key);
	while(item != NULL){
		if(strcmp(key, item->key_val) == 0){
			return item;
		}
		item = item->next;
	}
	return NULL;
}

#ifdef DEBUG 
void table_print_debug(struct table *tbl, FILE *stream){
	fprintf(stream, "<table p:%p size:%lu level:%d depth:%d >\n", tbl, tbl->size, tbl->level, tbl->depth);
	/* todo: add slots taken/available and total slot size */
	int slots_num;
	slots_num = size_by_level(tbl->level);
	fprintf(stream, "slots:%d\n", slots_num);
	int i;
	int first;
	struct table_item *slot = malloc(sizeof(struct table_item *));
	for(i=0; i < slots_num; i++){
		if(*(tbl->slots+i) == NULL){
			fprintf(stream, "%d\n", i);
		}else{
			fprintf(stream, "%d", i);
			slot = tbl->slots[i];
			first = 1;
			while(slot != NULL){
				if(first){
					first = 0;
					fprintf(stream, " ");
				}else{
					fprintf(stream, ", ");
				}
				fprintf(stream, "%s->%s", slot->key_val, slot->content);
				slot = slot->next;
			}
			fprintf(stream, "\n");
		}
	}

	/* table data */
		/* climb slots */
		/* climb to the end of each slot */
		/* present data about how many queries it takes to get to each item */

}
#endif
/*
void *table_remove(struct table *tbl, void *key);
*/
