#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include "err.h"
#include "arr.h"
#include "util.h"
#include "table.h"

int test_print_eq(struct arr *a, char *s, char *title){
  struct arr *msg = arr_alloc(4);
  int r;
  if((r = str_eq(a->v, s, a->c)) == 0){
    arr_insert(msg, msg->c, ".", 1);
    write(1, msg->v, msg->c);
    return 0;
  }else{
		/*
    arr_append_cstr(msg, "fail - ");
    arr_append_cstr(msg, title);
    arr_append_cstr(msg, ":");
    arr_append_int_str(msg, r);
    arr_append_cstr(msg, ":");
		*/
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
  int ret = 0;
  write_cstr(1, ">>> test >>>\n");
  struct arr *a = arr_alloc(4);
  arr_insert(a, 0, "this", 4);
  ret |= test_print_eq(a, "this", "arr 0");
  arr_insert(a, a->c, " is", 3);
  test_print_eq(a, "this is", "arr 0.1");
  arr_insert(a, 0, "hi ", 3);
  test_print_eq(a, "hi this is", "arr 0.2");
  arr_insert(a, 0, "this is a big string being added. ", strlen("this is a big string being added. "));
  test_print_eq(a, "this is a big string being added. hi this is", "arr 1");
  struct arr *b = arr_alloc(4);
  arr_insert(b, 0, "starting:", strlen("starting:"));
  test_print_eq(b, "starting:", "arr 2");
  arr_append_int_str(b, 3);
  test_print_eq(b, "starting:3", "arr 3");
  arr_append_int_str(b, 40012);
  ret |= test_print_eq(b, "starting:340012", "arr 4");
  struct arr *c = arr_alloc(4);
  arr_append(c, "h");
  arr_append(c, "i");
  test_print_eq(c, "hi", "arr 5");
  write(1, "\n", 1);
  return ret;
}

int test_uarr_ptr(){
  int ret = 0, l, ip;
  struct arr *msg = arr_alloc(16);
  struct uarr *p = uarr_alloc(2, sizeof(char *));
  char *carr[] = {"hi","there","alpha","beta"};
  uarr_append(p, &carr[0]);
  uarr_append(p, &carr[1]);
  uarr_append(p, &carr[2]);
  uarr_append(p, &carr[3]);
  char **cp = (char **)p->v;
  l = uarr_count(p);
  while(l--){
    arr_insert(msg, msg->c, *cp, strlen(*cp));
    arr_insert(msg, msg->c, ",", 1);
    cp++;
  }
  ret |= test_print_eq(msg, "hi,there,alpha,beta,", "uarr ptr 1");
  arr_free(msg);
  uarr_free(p);
  write(1, "\n", 1);
  return ret;
}

int test_uarr(){
  int ret = 0;
  write_cstr(1, ">>> test_uarr >>>\n");
  int l;

  /* test insert & append */
  struct arr *msg = arr_alloc(16);
  struct uarr *p = uarr_alloc(4, sizeof(int));
  int iarr[] = {1,2,3,4};
  uarr_insert(p, uarr_count(p), &iarr[0], 1);
  uarr_insert(p, uarr_count(p), &iarr[1], 1);
  uarr_append(p, &iarr[2]);
  uarr_append(p, &iarr[3]);
  int *ip = (int *)p->v;
  l = uarr_count(p);
  while(l--){
    arr_append_int_str(msg, *ip);
    arr_insert(msg, msg->c, ",", 1);
    ip++;
  }
  ret |= test_print_eq(msg, "1,2,3,4,", "uarr 1");
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
    arr_append_int_str(msg2, *ip2);
    arr_insert(msg2, msg2->c, ",", 1);
    ip2++;
  }
  ret |= test_print_eq(msg2, "1,2,3,4,", "uarr 2");
  arr_free(msg2);
  uarr_free(p2);
  write(1, "\n", 1);
  ret |= test_uarr_ptr();
  return ret;
}

char *string_copy(char *str){
	int len = strlen(str)+1;
	char *dest = malloc(sizeof(char)*len);
	memmove(dest, str, len); 
	return dest;
}

int test_table(){
  write_cstr(1, ">>> table >>>\n");
	struct table *tbl;
	tbl = table_alloc();
	int hash = 0;
	puts("--- testing hash ---");
	hash = hash_key(tbl, "hi");
	printf("result hi %d\n", hash);
	hash = hash_key(tbl, "hello");
	printf("result hello %d\n", hash);
	hash = hash_key(tbl, "denial");
	printf("result denial %d\n", hash);
	hash = hash_key(tbl, "I was a donkey once upon a time");
	printf("result I was a donkey once upon a time %d\n", hash);
	hash = hash_key(tbl, "dominence");
	printf("result what's dominence %d\n", hash);
	hash = hash_key(tbl, "power up it's drinking time");
	printf("result power up it's drinking time %d\n", hash);

	puts("--- testing size by level ---");
	printf("size by level 1:%d\n", size_by_level(1));
	printf("size by level 2:%d\n", size_by_level(2));
	printf("size by level 3:%d\n", size_by_level(3));

	puts("--- testing values and add ---");

	table_add(tbl, string_copy("hello"), string_copy("there"));
	table_print_debug(tbl, stdout);
	table_add(tbl, string_copy("apple"), string_copy("tree"));
	table_print_debug(tbl, stdout);
	table_add(tbl, string_copy("bannana"), string_copy("split"));
	table_print_debug(tbl, stdout);
	table_add(tbl, string_copy("lash"), string_copy("O'Ninetails"));
	table_print_debug(tbl, stdout);
	table_add(tbl, string_copy("fire"), string_copy("crow"));
	table_print_debug(tbl, stdout);
	table_add(tbl, string_copy("denial"), string_copy("is hidden"));
	table_print_debug(tbl, stdout);
	table_add(tbl, string_copy("one"), string_copy("1"));
	table_print_debug(tbl, stdout);
	table_add(tbl, string_copy("two"), string_copy("2"));
	table_print_debug(tbl, stdout);
	table_add(tbl, string_copy("three"), string_copy("3"));
	table_print_debug(tbl, stdout);
	table_add(tbl, string_copy("four"), string_copy("4"));
	table_print_debug(tbl, stdout);
	table_add(tbl, string_copy("five"), string_copy("5"));
	table_print_debug(tbl, stdout);
	table_add(tbl, string_copy("six"), string_copy("6"));
	table_print_debug(tbl, stdout);
	table_add(tbl, string_copy("seven"), string_copy("7"));
	table_print_debug(tbl, stdout);
	table_add(tbl, string_copy("eight"), string_copy("8"));
	table_print_debug(tbl, stdout);
	table_add(tbl, string_copy("nine"), string_copy("9"));
	table_print_debug(tbl, stdout);
	table_add(tbl, string_copy("ten"), string_copy("10"));
	table_print_debug(tbl, stdout);
	table_add(tbl, string_copy("eleven"), string_copy("11"));
	table_print_debug(tbl, stdout);
	table_add(tbl, string_copy("twelve"), string_copy("12"));
	table_print_debug(tbl, stdout);
	table_add(tbl, string_copy("thirteen"), string_copy("13"));
	table_print_debug(tbl, stdout);
	table_add(tbl, string_copy("fourteen"), string_copy("14"));
	table_print_debug(tbl, stdout);
	table_add(tbl, string_copy("fifteen"), string_copy("15"));
	table_print_debug(tbl, stdout);
	table_add(tbl, string_copy("sixteen"), string_copy("16"));
	table_print_debug(tbl, stdout);
	table_add(tbl, string_copy("seventeen"), string_copy("17"));
	table_print_debug(tbl, stdout);
	table_add(tbl, string_copy("eighteen"), string_copy("18"));
	table_print_debug(tbl, stdout);
	table_add(tbl, string_copy("nineteen"), string_copy("19"));
	table_print_debug(tbl, stdout);
	table_add(tbl, string_copy("twenty"), string_copy("20"));
	table_print_debug(tbl, stdout);

	puts("--- testing get ---");
	struct table_item *item = table_get(tbl, "hello");
	if(item != NULL){
		fprintf(stdout, "%s->%s\n", item->key_val, item->content);
	}
	struct table_item *item2 = table_get(tbl, "not here");
	if(item2 != NULL){
		fprintf(stdout, "%s->%s\n", item2->key_val, item2->content);
	}else{
		puts("item is null");
	}
	struct table_item *item3 = table_get(tbl, "bannana");
	if(item3 != NULL){
		fprintf(stdout, "%s->%s\n", item3->key_val, item3->content);
	}
	struct table_item *item4 = table_get(tbl, "one");
	if(item4 != NULL){
		fprintf(stdout, "%s->%s\n", item4->key_val, item4->content);
	}

	return 0;
}

int main(){ 
  int ret = 0;
  /*ret |= test();*/
  ret |= test_uarr();
  ret |= test_table();
  return ret;
}
