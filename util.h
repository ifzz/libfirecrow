struct arr *arr_from_cstr(char *p);
int arr_append_int_str(struct arr *a, int i);
int arr_append_cstr(struct arr *a, char *p);
/* write output to the file descriptor in chunks
 * of chunk_size end when a '\0' is encountered
 *
 * bytes_written = write_cstr(fd, cstr);
 */
int write_cstr(int, char *);
int write_int(int fd, int i);

#define SP_CHILD (uint32_t)1
#define SP_PARENT (uint32_t)2 
/* subproc */
struct subproc {
   pid_t pid;
   int in;
   int out;
   int err;
   struct uarr *arg;/* char ** */
   int flags;
};

int fork_wpipes(char **argv, struct subproc *sp);
