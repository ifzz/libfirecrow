#include "err.h"
#include "arr.h"
#include <stdio.h>

int main(){ 
	struct arr *a = arr_alloc(4);

	arr_insert(a, 0, "this", 4);
	write(1, "\"", 1);
	write(1, a->v, a->c);
	write(1, "\"", 1);

	char s[] = "hi here is a string\n";
	int i, l;
	char *p;
	for(p = s, l = sizeof(s); l--; p++){
		write(1, p, 1);
		if(a->c+1 > a->a){
			arr_resize(a, a->c+1);
			printf("\nresizing: %d\n", a->a);
		}
		*(a->v+(a->c++)) = *p;
	}
	write(1, a->v, a->c);
	arr_insert(a, 7, "t", 1);
	write(1, a->v, a->c);
	arr_remove(a, 0, 4, ARR_NORESULT);
	write(1, a->v, a->c);

	struct arr *r = arr_remove(a, 3, 11, ARR_RESULT);
	write(1, r->v, r->c);
	write(1, "\n", 1);

	struct arr *r2 = arr_slice(r, 0, 5, ARR_RESULT);
	write(1, r2->v, r2->c);
	write(1, "\n", 1);

	arr_slice(r, 0, 2, ARR_NORESULT);
	write(1, r->v, r->c);
	write(1, "\n", 1);

	struct arr *m = arr_from_cstr("a new string here");
	write(1, m->v, m->c);
	write(1, "\n", 1);

	return 0;
}
