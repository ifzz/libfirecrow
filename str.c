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
	s->s = malloc(l);
	if(s->s == NULL){
		ERR("mkstr char string alloc", 1);
	}
	memmove(s->s, cstr, s->l);
	return s;
}

char *cstr(struct str *s){
	char *cs = malloc(s->l+1);
	if(cs == NULL){
		ERR("cstr char string alloc", 1);
	}
	memmove(cs, s->s, s->l);
	*(cs+s->l) = 0;
	return cs;
}

int freestr(struct str *str){
	free(str->s);
	free(str);
	return OK;
}
