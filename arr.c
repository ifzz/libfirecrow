#include <stdlib.h>
#include <sys/types.h>
#include "arr.h"
#include "err.h"

/* arr = arr_alloc(); */
struct arr *arr_alloc(int amount){
	struct arr *a = (struct arr *) alloc_or_die(sizeof(struct arr), "arr_alloc allocating struct", 1);
	if(amount > 0){
		char *v = (char *) alloc_or_die((size_t) amount, "arr_alloc allocating value", 1);
		a->v = v;
		a->c = 0;
		a->a = amount;
	}
	return a;
}

