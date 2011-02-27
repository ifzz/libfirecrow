#include "err.h"
#include "arr.h"
#include "util.h"
#include <string.h>
#include <stdio.h>

int test_print_eq(struct arr *a, char *s){
  struct arr *msg = arr_alloc(4);
  int r;
  if((r = str_eq(a->v, s, a->c)) == 0){
    arr_insert(msg, msg->c, ".", 1);
    write(1, msg->v, msg->c);
    return 0;
  }else{
    arr_append_cstr(msg, "mismatch:");
    arr_append_int_str(msg, r);
    arr_append_cstr(msg, ":");
    write(1, msg->v, msg->c);
    write(1, a->v, a->c);
    return 123;
  }
}

int str_eq(char *a, char *b, int l){
  int i = 0;
  while(l--){
    if(*a++ != *b++)
      return i;
    i++;
  }
  return 0;
}

int test(){
  int ret;
  write_cstr(1, ">>> test >>>\n");
  struct arr *a = arr_alloc(4);
  arr_insert(a, 0, "this", 4);
  ret |= test_print_eq(a, "this");
  arr_insert(a, a->c, " is", 3);
  test_print_eq(a, "this is");
  arr_insert(a, 0, "hi ", 3);
  test_print_eq(a, "hi this is");
  arr_insert(a, 0, "this is a big string being added. ", strlen("this is a big string being added. "));
  test_print_eq(a, "this is a big string being added. hi this is");
  struct arr *b = arr_alloc(4);
  arr_insert(b, 0, "starting:", strlen("starting:"));
  test_print_eq(b, "starting:");
  arr_append_int_str(b, 3);
  test_print_eq(b, "starting:3");
  arr_append_int_str(b, 40012);
  ret |= test_print_eq(b, "starting:340012");
  struct arr *c = arr_alloc(4);
  arr_append(c, "h");
  arr_append(c, "i");
  test_print_eq(c, "hi");
  write(1, "\n", 1);
  return ret;
}

int test_uarr(){
  int ret;
  write_cstr(1, ">>> test_uarr >>>\n");

  /* test insert & append */
  struct arr *msg = arr_alloc(16);
  struct uarr *p = uarr_alloc(4, sizeof(int));
  int iarr[] = {1,2,3,4};
  uarr_insert(p, uarr_count(p), &iarr[0], 1);
  uarr_insert(p, uarr_count(p), &iarr[1], 1);
  uarr_append(p, &iarr[2]);
  uarr_append(p, &iarr[3]);
  int *ip = (int *)p->v;
  int l = uarr_count(p);
  while(l--){
    arr_append_int_str(msg, *ip);
    arr_insert(msg, msg->c, ",", 1);
    ip++;
  }
  ret |= test_print_eq(msg, "1,2,3,4,");
  arr_free(msg);
  uarr_free(p);
  write(1, "\n", 1);

  /* test append */
  struct arr *msg2 = arr_alloc(16);
  struct uarr *p2 = uarr_alloc(4, sizeof(int));
  int iarr2[] = {1,2,3,4};
  uarr_append(p2, &iarr2[0]);
  uarr_append(p2, &iarr2[1]);
  uarr_append(p2, &iarr2[2]);
  uarr_append(p2, &iarr2[3]);
  int *ip2 = (int *)p2->v;
  l = uarr_count(p2);
  while(l--){
    arr_append_int_str(msg, *ip2);
    arr_insert(msg, msg->c, ",", 1);
    ip++;
  }
  ret |= test_print_eq(msg, "1,2,3,4,");
  arr_free(msg);
  uarr_free(p2);
  write(1, "\n", 1);
  return ret;
}

int main(){ 
  int ret;
  ret |= test();
  ret |= test_uarr();
  return ret;
}
