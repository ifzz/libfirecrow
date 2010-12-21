/* write output to the file descriptor in chunks
 * of chunk_size end when a '\0' is encountered
 *
 * bytes_written = write_cstr(fd, cstr, chunk_size);
 */
int write_cstr(int, char *, int);
