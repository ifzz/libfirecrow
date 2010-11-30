#include <stdio.h>
#include <stdlib.h>

void err(char *name, int code){
	printf("error %d:%s", code, name);
	exit(code);
}

void *alloc_or_die(size_t size, char *name, int code){
	void *p = malloc(size);
	if(p == NULL){
		err(name, code);
		/* exit called in err, never return */
	}
	return p;
}
