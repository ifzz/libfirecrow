#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include "arr.h"
#include "err.h"

#include <stdio.h>

void arr_init__(struct arr *a, int amount){
  a->c = 0;
  if(amount > 0){
    char *v = (char *) die_if_null(malloc((size_t) amount), 
      "arr_alloc allocating value", ERROR);
    a->v = v;
    a->a = amount;
  }else{
    a->a = 0;
  }
}

/* arr = arr_alloc(amount); */
struct arr *arr_alloc(int amount){
  struct arr *a; 
  a = (struct arr *) die_if_null(malloc(sizeof(struct arr)), 
    "arr_alloc allocating struct", ERROR);
  arr_init__(a, amount);  
  return a;
}

/* arr_clear(arr) */
void arr_clear(struct arr *ap){
  ap->c = 0;
}

/* arr_free(arr) */
void arr_free(struct arr *ap){
  free(ap->v);
  free(ap);
}

/* resizes if necessary */
static int arr_resize(struct arr *ap, int size){
  int sz = ap->a;
  if(sz < size){
    if(sz <= 0) sz = 2;
    while(sz < size){
      sz *= 2;
    }
    /* reallocate content */
    ap->v = die_if_null(realloc(ap->v, sz), 
      "arr_resize allocating new memory", ERROR);
    ap->a = sz;  
  }
  return ap->a;
}

int arr_insert(struct arr *ap, int index, void *src, int count){
	arr_resize(ap, ap->a+count);
	memmove(ap->v+index+count, ap->v+index, count);
  memcpy(ap->v+index, src, count);
  return index;
}

/* result_size = arr_remove(arr, start, end, result);
 * or arr_remove(arr, start, end, NULL); 
 */
struct arr *arr_remove(struct arr *ap, int start, int end, int flags){
  int sz = end-start;
  int esz = ap->c-end;
  struct arr *rp;
  if(esz < 0){
    err("index out of range", WARN);
    return NULL;
  }
  if(flags & ARR_RESULT){
    rp = arr_alloc(sz);
    arr_insert(rp, 0, ap->v+start, sz);
  }
  if(esz != 0){
    memmove(ap->v+start, ap->v+end, esz);
  }
  ap->c = start+esz;
  if(flags & ARR_RESULT)
    return rp; 
  else
    return NULL;
}

/* result_size = arr_slice(arr, start, end, result);
 * or arr_slice(arr, start, end, NULL);
 */
struct arr *arr_slice(struct arr *ap, int start, int end, int flags){
  int sz = end-start;
  if(start+sz > ap->c){
    err("index out of range", WARN);
    return NULL;
  }
  struct arr *rp;
  if(flags & ARR_RESULT){
    rp = arr_alloc(sz);
    arr_insert(rp, 0, ap->v+start, sz);
    return rp;
  }else{
    if(sz != ap->c){
      memmove(ap->v, ap->v+start, sz);
      ap->c = sz;
    }
    return NULL;
  }
}

struct uarr *uarr_alloc(int size, int unit_size){
  struct uarr *a; 
  a = (struct uarr *) die_if_null(malloc(sizeof(struct uarr)), 
    "arr_alloc allocating struct", ERROR);
  arr_init__((struct arr *)a, size*unit_size);
  a->u = unit_size;
  return a;
}

