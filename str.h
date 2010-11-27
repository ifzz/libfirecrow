struct str {
	char *s;/* the character array*/
	int l;/* length */
};

struct str *mkstr(char *);
int freestr(struct str *);
char *cstr(struct str *);
