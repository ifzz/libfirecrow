#include <stdlib.h>
#include <sys/types.h>
#include "arr.h"
#include "err.h"

/* arr = arr_alloc(amount); */
struct arr *arr_alloc(int amount){
	struct arr *a; 
	a = (struct arr *) die_if_null(malloc(sizeof(struct arr)), 
		"arr_alloc allocating struct", 1);
	a->c = 0;
	if(amount > 0){
		char *v = (char *) die_if_null(malloc((size_t) amount), 
			"arr_alloc allocating value", 1);
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
			"arr_resize allocating new memory", 1);
	  ap->a = sz;	
	}
	return ap->a;
}
