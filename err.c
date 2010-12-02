#include <stdio.h>
#include <stdlib.h>

void err(char *name, int code){
	printf("error %d:%s", code, name);
	exit(code);
}

void *die_if_null(void *p, char *name, int code){
	if(p == NULL){
		err(name, code);
		/* exit called in err, never return */
	}
	return p;
}
