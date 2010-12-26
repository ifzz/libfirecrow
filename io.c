#include <unistd.h>

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
