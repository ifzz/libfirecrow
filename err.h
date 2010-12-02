#define ERR err
#define OK 0

#include <sys/types.h>

int err(char *, int);

void *die_if_null(void *, char *, int);
