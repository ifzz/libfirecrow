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

extern int fork_wpipes(char **argv, struct subproc *sp){
  /* open pipes */
  int pid, fds[3][2];
  ERR_IF_LZ( pipe( fds[0] ), "error opening stdin pipe" );
  ERR_IF_LZ( pipe( fds[1] ), "error opening stdout pipe" );
  ERR_IF_LZ( pipe( fds[2] ), "error opening stderr pipe" );
  ERR_IF_LZ( (pid = fork()), "error fork unsuccessful" );
  struct subproc s = *sp;
  if(pid == 0){
    ERR_IF_LZ( dup2( fds[0][0], 0 ), "error duplicating stderr" );
    ERR_IF_LZ( dup2( fds[1][1], 1 ), "error duplicating stdout" );
    ERR_IF_LZ( dup2( fds[2][1], 2 ), "error duplicating stdin" );
    close( fds[0][1] );
    close( fds[1][0] );
    close( fds[2][0] );
    s.pid = 0;
    s.in = fd[0][0];
    s.out = fd[1][1];
    s.err = fd[2][1];
    s.flags = SP_CHILD;
    return 0;
  }else{
    close( fds[0][0] );
    close( fds[1][1] );
    close( fds[2][1] );
    s.pid = pid;
    s.in = fd[0][1];
    s.out = fd[1][0];
    s.err = fd[2][0];
    s.flags = SP_PARENT;
    return 0;
  }
}

