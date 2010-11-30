#include "err.h"
#include "arr.h"

int main(){ 
	struct arr *a = arr_alloc(4);
	*(a->v+(a->c++)) = 'h';
	*(a->v+(a->c++)) = 'i';
	*(a->v+(a->c++)) = '\n';
	write(1, a->v, a->c);
	return 0;
}
