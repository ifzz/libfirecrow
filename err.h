#define ERR err
#define OK 0

#include <sys/types.h>

int err(char *, int);

int alloc_or_die(size_t, char *, int);
