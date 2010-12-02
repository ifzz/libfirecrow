#include "err.h"
#include "arr.h"
#include <stdio.h>

int main(){ 
	struct arr *a = arr_alloc(4);
	
	char s[] = "hi here is a string\n";
	int i, l;
	char *p;
	printf("\nstarting size: %d\n", a->a);
	for(p = s, l = sizeof(s); l--; p++){
		write(1, p, 1);
		if(a->c+1 > a->a){
			arr_resize(a, a->c+1);
			printf("\nresizing: %d\n", a->a);
		}
		*(a->v+(a->c++)) = *p;
	} 

	/*
	*(a->v+(a->c++)) = 'h';
	*(a->v+(a->c++)) = 'i';
	*(a->v+(a->c++)) = '\n';
	*/
	write(1, a->v, a->c);
	return 0;
}
