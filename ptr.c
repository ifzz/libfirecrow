#include <ptr.h>

extern void *ptr_alloc(int levels){
  return malloc(sizeof(void *));
}

extern void **dptr_alloc(int levels){
  void *d =  malloc(sizeof(void *));
  void *p = NULL;
  *d = p;
  return d;
}
