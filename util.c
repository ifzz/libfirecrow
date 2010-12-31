#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "arr.h"

/* arr = arr_alloc(string); */
struct arr *arr_from_cstr(char *p){
  struct arr *rp=arr_alloc(4);
  int sz = 0;
  char *cp = p;
  while(*cp++ != 0){
    sz++;
  }
  arr_insert(rp, 0, p, sz);
  return rp;
}

int arr_append_int_str(struct arr *a, int i){
  char buff[32];
  int r = snprintf(buff, 32, "%d", i);
  arr_insert(a, a->c, &buff, r);
  return a->c; 
}

int arr_append_cstr(struct arr *a, char *p){
  arr_insert(a, a->c, p, strlen(p));
  return a->c;
}

int write_cstr(int fd, char *cstr){
  char *p, *seg;
  p = seg = cstr;
  int i = 0, r = 0;
  int chunk_size = 16;  
  while(*(p++) != '\0'){
    if(++i >= chunk_size){
      r += write(fd, seg, i); 
      i = 0;
      seg = p;
    } 
  }
  if(i != 0){
    r += write(fd, seg, i); 
  }
  return r;
}

int write_int(int fd, int i){
  char buff[32];
  int r = snprintf(buff, 32, "%d", i);
  write(fd, buff, r);
}

