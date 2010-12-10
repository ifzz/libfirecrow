#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include "arr.h"
#include "err.h"

#include <stdio.h>

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

/* arr = arr_alloc(string); */
struct arr *arr_from_cstr(char *p){
	struct arr *rp= arr_alloc(4);
	int sz = 0;
	char *cp = p;
	while(*cp++ != 0){
		sz++;
	}
	arr_insert(rp, 0, p, sz);
	return rp;
}

/* size = arr_resize(arr, size); */
/* TODO: add downsize also if the system is larger */
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

/* result_size = arr_remove(arr, start, end, result);
 * or arr_remove(arr, start, end, NULL); 
 */
struct arr *arr_remove(struct arr *ap, int start, int end, int flags){
	int sz = end-start;
	int esz = ap->c-end;
	struct arr *rp;
	if(esz < 0){
		err("index out of range", WARN);
		return NULL;
	}
	if(flags & ARR_RESULT){
		rp = arr_alloc(sz);
		arr_insert(rp, 0, ap->v+start, sz);
	}
	if(esz != 0){
		memmove(ap->v+start, ap->v+end, esz);
	}
	ap->c = start+esz;
	if(flags & ARR_RESULT)
		return rp; 
	else
		return NULL;
}

/* result_size = arr_slice(arr, start, end, result);
 * or arr_slice(arr, start, end, NULL);
 */
struct arr *arr_slice(struct arr *ap, int start, int end, int flags){
	int sz = end-start;
	if(start+sz > ap->c){
		err("index out of range", WARN);
		return NULL;
	}
	struct arr *rp;
	if(flags & ARR_RESULT){
		rp = arr_alloc(sz);
		arr_insert(rp, 0, ap->v+start, sz);
		return rp;
	}else{
		if(sz != ap->c){
			memmove(ap->v, ap->v+start, sz);
			ap->c = sz;
		}
		return NULL;
	}
}
