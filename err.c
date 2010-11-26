#include <stdio.h>
#include <stdlib.h>

int err(char *name, int code){
	printf("error %d:%s", code, name);
	exit(code);
}
