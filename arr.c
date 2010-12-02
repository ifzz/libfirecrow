#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include "arr.h"
#include "err.h"

/* arr = arr_alloc(amount); */
struct arr *arr_alloc(int amount){
	struct arr *a; 
	a = (struct arr *) die_if_null(malloc(sizeof(struct arr)), 
		"arr_alloc allocating struct", ERROR);
	a->c = 0;
	if(amount > 0){
		char *v = (char *) die_if_null(malloc((size_t) amount), 
			"arr_alloc allocating value", ERROR);
		a->v = v;
		a->a = amount;
	}else{
		a->a = 0;
	}
	return a;
}

/* size = arr_resize(arr, size); */
int arr_resize(struct arr *ap, int size){
	int sz = ap->a;
	if(sz < size){
		while(sz < size){
			sz *= 2;
		}
		/* reallocate content */
		ap->v = die_if_null(realloc(ap->v, sz), 
			"arr_resize allocating new memory", ERROR);
	  ap->a = sz;	
	}
	return ap->a;
}

/* index = arr_insert(arr, source, count, index); */
int arr_insert(struct arr *ap, int index, void *src, int count){
	if(index > ap->c){
		err("index out of range", WARN);
		return -1;
	}
	int sz = ap->c+count;
	if(sz > ap->a){
		arr_resize(ap, sz);
	}
	if(index+count <= ap->c){
		memmove(ap->v+(index+count), ap->v+index, ap->c-index);
	}
	memcpy(ap->v+index, src, count);
	ap->c = sz;
	return index;
}
