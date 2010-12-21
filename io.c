#include <unistd.h>

/* write output to the file descriptor in chunks
 * of chunk_size end when a '\0' is encountered
 */
int write_cstr(int fd, char *cstr, int chunk_size){
	char *p, *seg;
	p = seg = cstr;
	int i = 0, r = 0;
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
