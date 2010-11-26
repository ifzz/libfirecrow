#include <string.h>
#include <stdlib.h>
#include "err.h"
#include "str.h"

struct str *mkstr(char *cstr){
	struct str *s = malloc(sizeof(struct str));
	if(s == NULL){
		ERR("mkstr struct str alloc", 1);
	}
	int l = strlen(cstr);
	s->l = l;
	s->s = malloc(l+1);
	if(s->s == NULL){
		ERR("mkstr char string alloc", 1);
	}
	s->s = memmove(s->s, cstr, s->l);
	*(s->s+l) = 0; 
	return s;
}

int freestr(struct str *str){
	free(str->s);
	free(str);
	return OK;
}
