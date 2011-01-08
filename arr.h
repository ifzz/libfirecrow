
#define ARR_RESULT 1
#define ARR_NORESULT 0

struct arr {
  char *v;/* content of the array */
  int c;/* count of bytes filled with content  */
  int a;/* allocated bytes for the content */
};

/* arr = arr_alloc(start_amount); */
struct arr *arr_alloc(int);

/* arr_clear(arr) */
void arr_clear(struct arr *);

/* arr_free(arr) */
void arr_free(struct arr *);

/* arr = arr_alloc(string); */
struct arr *arr_from_cstr(char *);

/* size = arr_resize(arr, size); */
int arr_resize(struct arr *, int);

/* index = arr_insert(arr, index, source, count); */
int arr_insert(struct arr *, int, void *, int);

/* res = arr_remove(arr, start, end, result);
 * or arr_remove(arr, start, end, NULL); 
 */
struct arr *arr_remove(struct arr *, int, int, int flags);

/* res = arr_slice(arr, start, end, result);
 * or arr_slice(arr, start, end, NULL);
 */
struct arr *arr_slice(struct arr *, int, int, int flags);

/* unit specific array - holds multibyte values */
struct uarr {
  char *v;/* content of the array */
  int c;/* count of bytes filled with content  */
  int a;/* allocated bytes for the content */
  int u;/* bytes per unit */
};

/* item_i = uarr_nth(arr, i);*/
int uarr_nth(struct uarr *, int);

/* rest of uarr functions are the same as their respective
 arr functions, but arithmetic to get the byte address
 from the unit size is done.

 e.g.

   struct uarr x = {"aabbccddee", 10, 10, 2};
   char *c = uarr_nth(&x, 3);
   write(1, c, 2);// writes 'cc'

 wheras with regular uarr your would pass in the absolute
 address 5 instead of 3 to get a pointer to 'cc' in
 the above string:

   char *c = &(x.v+5);
 
*/
struct uarr *uarr_alloc(int, int);
#define uarr_free(a) arr_free((struct arr *)a)
#define uarr_insert(arr, index, src, count) arr_insert(arr, index*arr->u, src, count*arr->u)
int uarr_remove(struct uarr *, int, int, void *);
int uarr_slice(struct uarr *, int, int, void *);
