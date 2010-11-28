struct str {
	char *s;/* the character array*/
	int c;/* count of items in the array */
	int a;/* allocated size of character array*/
};

struct str *mkstr(char *);
int freestr(struct str *);
char *cstr(struct str *);
