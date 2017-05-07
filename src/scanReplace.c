/*
 This is free and unencumbered software released into the public domain.
 
 Anyone is free to copy, modify, publish, use, compile, sell, or
 distribute this software, either in source code form or as a compiled
 binary, for any purpose, commercial or non-commercial, and by any
 means.
 
 In jurisdictions that recognize copyright laws, the author or authors
 of this software dedicate any and all copyright interest in the
 software to the public domain. We make this dedication for the benefit
 of the public at large and to the detriment of our heirs and
 successors. We intend this dedication to be an overt act of
 relinquishment in perpetuity of all present and future rights to this
 software under copyright law.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 OTHER DEALINGS IN THE SOFTWARE.
 
 For more information, please refer to <http://unlicense.org/>
 */



#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <err.h>
#include <string.h>



char *      find_match(
    const
    char        *buf,
    const
    char        *buf_end,
    const
    char        *pat,
    size_t      len
)
{
    ptrdiff_t   i;
    const
    char        *start = buf;
    
    while (start + len < buf_end) {
        for (i = 0; i < len; i++) {
            if (start[i] != pat[i]) {
                break;
            }
        }
							 
        if (i == len)
            return (char *)start;
        start++;
    }
    
    return NULL;
}



int     replace(const char *from, const char *to, const char *fname)
{
#define bail(msg) { warn(msg" '%s'", fname); goto done; }
    struct stat     st;
    int             ret = 0;
    char            *buf = 0, *start, *end;
    size_t          len = strlen(from);
    size_t          nlen = strlen(to);
    int             fd = open(fname, O_RDWR);
						 
    if (fd == -1)
        bail("Can't open");
    if (fstat(fd, &st) == -1)
        bail("Can't stat");
    
    if (!(buf = malloc(st.st_size)))
        bail("Can't alloc");
    if (read(fd, buf, st.st_size) != st.st_size)
        bail("Bad read");
										 
    start = buf;
    end = find_match(start, buf + st.st_size, from, len);
    if (!end) /* no match found, don't change file */
        goto done;
    
    ftruncate(fd, 0);
    lseek(fd, 0, 0);
    do {
        write(fd, start, end - start);	/* write content before match */
        write(fd, to, nlen);		/* write replacement of match */
        start = end + len;		/* skip to end of match */
                /* find match again */
        end = find_match(start, buf + st.st_size, from, len);
    } while (end);

    /* write leftover after last match */
    if (start < buf + st.st_size)
        write(fd, start, buf + st.st_size - start);
    
done:
    if (fd != -1)
        close(fd);
    if (buf)
        free(buf);
    return ret;
}




#ifdef XYZZY
int main()
{
    const
    char        *from = "Goodbye, London!";
    const
    char        *to   = "Hello, New York!";
    const
    char        *files[] = { "test1.txt", "test2.txt", "test3.txt" };
    int         i;
					 
    for (i = 0; i < sizeof(files)/sizeof(char*); i++) {
        replace(from, to, files[i]);
    }
						 
							return 0;
}
#endif



