#define ERR err
#define OK 0
#define ERROR 1
#define WARN 2

#include <sys/types.h>

int err(char *, int);

void *die_if_null(void *, char *, int);
