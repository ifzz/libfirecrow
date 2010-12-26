#include "err.h"
#include "arr.h"
#include "io.h"
#include <string.h>
#include <stdio.h>

void test_print_eq(struct arr *a, char *s){
	write(1, a->v, a->c);
	write(1, "=", 1);
	write_cstr(1, s);
	write(1, "\n", 1);
}

void test(){
	write_cstr(1, ">>> testing >>>\n");
	struct arr *a = arr_alloc(4);
	arr_insert(a, 0, "this", 4);
	test_print_eq(a, "this");
	arr_insert(a, a->c, " is", 3);
	test_print_eq(a, "this is");
	arr_insert(a, 0, "hi ", 3);
	test_print_eq(a, "hi this is");
	arr_insert(a, 0, "this is a big string being added. ", strlen("this is a big string being added. "));
	test_print_eq(a, "this is a big string being added. hi this is");
	struct arr *b = arr_alloc(4);
	arr_insert(b, 0, "starting:", strlen("starting:"));
	test_print_eq(b, "starting:");
	arr_append_int_str(b, 3);
	test_print_eq(b, "starting:3");
	arr_append_int_str(b, 40012);
	test_print_eq(b, "starting:340012");
}

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

	test();
	return 0;
}
